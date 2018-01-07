// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>

#include <chrono>

#include <string>
#include <vector>
#include <unordered_map>

#include <thread>
#include <mutex>

#define CONCAT_(x,y) x##y
#define CONCAT(x,y) CONCAT_(x,y)

float now_seconds()
{
	return GetTickCount() / 1000.f;
}

struct Profiler
{
	struct PerScopeData
	{
		std::string name;
		float timeStart = FLT_MAX;
		float timeEnd = -FLT_MAX;
		std::vector<int> childIndices;
	};

	struct PerThreadData
	{
		std::vector<PerScopeData> m_scopesBuffer;
		std::vector<int> m_scopeStackIndices;
		std::vector<int> m_rootScopes;
	};

	std::unordered_map<std::thread::id, PerThreadData> m_perThreadProfiling;
	std::mutex m_perThreadDataLock;

	void push(std::string name)
	{
		PerThreadData* profile = nullptr;
		{
			std::lock_guard<std::mutex> lock(m_perThreadDataLock);
			profile = &m_perThreadProfiling[std::this_thread::get_id()];
		}

		if(profile->m_scopeStackIndices.size() == 0)
		{
			// In that case there is not current scope, so we should create a new one;
			profile->m_rootScopes.push_back(profile->m_scopesBuffer.size());
			profile->m_scopeStackIndices.push_back(profile->m_scopesBuffer.size());
		}
		else
		{
			// In that case there is already a scope, and we should add the new was as a child to it.
			profile->m_scopesBuffer[profile->m_scopeStackIndices.back()].childIndices.push_back(profile->m_scopesBuffer.size());
			profile->m_scopeStackIndices.push_back(profile->m_scopesBuffer.size());
		}

		// Actually allocate the new scope.
		profile->m_scopesBuffer.emplace_back(PerScopeData{});
		profile->m_scopesBuffer.back().name = name;
		profile->m_scopesBuffer.back().timeStart = now_seconds();
	}
	
	void pop()
	{
		PerThreadData* profile = nullptr;
		{
			std::lock_guard<std::mutex> lock(m_perThreadDataLock);
			profile = &m_perThreadProfiling[std::this_thread::get_id()];
		}

		if(profile->m_scopeStackIndices.size() > 0)
		{
			profile->m_scopesBuffer[profile->m_scopeStackIndices.back()].timeEnd = now_seconds();
			profile->m_scopeStackIndices.pop_back();
		}
		else
		{
			// Should never happen.
		}
	}
};

struct ProfilerScopeRAII
{
	Profiler* profiler = nullptr;

	ProfilerScopeRAII(Profiler* profiler, std::string scopeName)
		: profiler(profiler)
	{
		profiler->push(std::move(scopeName));
	}

	~ProfilerScopeRAII()
	{
		profiler->pop();
	}
};

#define SGE_ProfileFn(profiler) ProfilerScopeRAII const CONCAT(sge_profilerRAII_var_, __COUNTER__)(profiler, __FUNCTION__);
#define SGE_Profile(profiler, label) ProfilerScopeRAII const CONCAT(sge_profilerRAII_var_, __COUNTER__)(profiler, label);

Profiler g_profiler;


void drawPrintProfiling(const Profiler::PerThreadData* p, int i, int tabs)
{
	const auto& scope = p->m_scopesBuffer[i];
	for(int t = 0; t < tabs; ++t) printf("\t");
	printf("%s [%fs]\n", scope.name.c_str(), scope.timeEnd - scope.timeStart);

	for(int t = 0; t < scope.childIndices.size(); ++t)
	{
		drawPrintProfiling(p, scope.childIndices[t], tabs+1);
	}
};

void foo()
{
	SGE_ProfileFn(&g_profiler);
}

void bla()
{
	SGE_ProfileFn(&g_profiler);
	foo();
}

int main()
{
	
	{
		SGE_ProfileFn(&g_profiler);
		bla();W
	}

	bla();

	std::thread t(foo);
	std::thread t2(bla);
	t.join();
	t2.join();

	for(auto& perThread : g_profiler.m_perThreadProfiling)
	{
		printf("Thread\n\n");
		for(int t = 0; t < perThread.second.m_rootScopes.size(); ++t)
		{
			drawPrintProfiling(&perThread.second, perThread.second.m_rootScopes[t], 0);
		}
	}

	return 0;
}

