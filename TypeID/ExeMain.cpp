
#include "slib.h"
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct DLLHelper {
	HMODULE handle = 0;

	DLLHelper(const char* const dllPath = nullptr) {
		if (dllPath) {
			open(dllPath);
		}
	}

	bool open(const char* const dllPath) {
		handle = LoadLibraryA(dllPath);
		return handle != 0;
	}

	void* getAddr(const char* const symbol) const {
		return handle ? GetProcAddress(handle, symbol) : nullptr;
	}
};

#else
#include <dlfcn.h>
struct DLLHelper {
	void* handle = nullptr;

	DLLHelper(const char* const dllPath = nullptr) {
		if (dllPath) {
			open(dllPath);
		}
	}

	bool open(const char* const dllPath) {
		handle = dlopen(dllPath, RTLD_NOW);
		if (handle == nullptr) {
			printf(dlerror());
		}
		return handle != nullptr;
	}

	void* getAddr(const char* const symbol) const {
		return handle ? dlsym(handle, symbol) : nullptr;
	}
};
#endif

#include "PluginInterface.h"

enum TestEnum : int {
	te_0,
	te_1,
	te_2,
};

struct Storage {
	int z = 0;
	TestEnum a = te_0;

  public:
	const TestEnum& getA() const {
		return a;
	}
	void setA(const TestEnum& _) {
		a = _;
	}
};

struct Container {
	std::vector<Storage> v;
};

struct EvenBiggerContainer {
	Container container;
};

DefineTypeId(Storage, 10'00'00'0001);
DefineTypeId(std::vector<Storage>, 10'00'00'0002);
DefineTypeId(Container, 10'00'00'0003);
DefineTypeId(EvenBiggerContainer, 10'00'00'0004);
DefineTypeId(TestEnum, 10'00'00'0005);

ReflRegisterBlock("blah") {
	ReflAddType(TestEnum) ReflEnumVal(te_0, "te_0") ReflEnumVal(te_1, "te_1") ReflEnumVal(te_2, "te_2");

	ReflAddType(Container) ReflMemberRaw(Container, "v", v);

	ReflAddType(std::vector<Storage>);
	ReflAddType(Storage) ReflMemberRaw(Storage, "z", z) ReflMember(Storage, TestEnum, "a", getA, setA);

	ReflAddType(EvenBiggerContainer) ReflMemberRaw(EvenBiggerContainer, "container", container);
}

int main(int argc, char* argv[]) {
	SLibType s;
	// s.foo();
	typeLib().setPluginID(1);
	typeLib().performRegistration();

	auto& r = typeLib();

	EvenBiggerContainer c;

	c.container.v.resize(5);
	c.container.v[3].a = te_1;

	MemberChain chain;
	chain.add(r.find(sgeTypeId(EvenBiggerContainer))->find1stMember("container"));
	chain.add(r.find(sgeTypeId(Container))->find1stMember("v"), 3);
	chain.add(r.find(sgeTypeId(Storage))->find1stMember("a"));

	MemberAccessor ma = chain.follow(&c);

	TestEnum value = ma.get<TestEnum>().value();
	ma.set(te_2);

	DLLHelper dll("dlib.dll");
	AllocatePluginInterfaceFnPtr allocInterfaceFnPtr = (AllocatePluginInterfaceFnPtr)dll.getAddr("allocateInterface");

	IPluginInterface* plugin = allocInterfaceFnPtr();
	plugin->onLoad();
	plugin->updateTypes(typeLib());
	typeLib().obtainTypesFrom(plugin->getPluginTypeRegister());

	const TypeDesc* tdX = typeLib().findByName("X");
	void* xVar = tdX->newFn();

	for (int t = 0; t < tdX->numMembers(); ++t) {
		const MemberDesc* md = tdX->getMember(t);
		int v;
		md->callGetter(xVar, &v);
		int breakPointHelper0 = 100;
	}

	for (int t = 0; t < tdX->numMembers(); ++t) {
		const MemberDesc* md = tdX->getMember(t);
		md->callSetter(xVar, &t);
		int breakPointHelper0 = 100;
	}

	for (int t = 0; t < tdX->numMembers(); ++t) {
		const MemberDesc* md = tdX->getMember(t);
		int v;
		md->callGetter(xVar, &v);
		int breakPointHelper0 = 100;
	}

	chain.clear();
	chain.add(tdX->find1stMember("b"));
	int dllValue = chain.follow(xVar).get<int>().value();
	chain.follow(xVar).set(5000);
	dllValue = chain.follow(xVar).get<int>().value();

	for (auto tdItr : r.getAllTypes()) {
		auto td = tdItr.second;
		int numMembers = td.numMembers();
		printf("%s %d\n", td.getTypeName(), td.typeId.id);
		for (int t = 0; t < numMembers; ++t) {
			const MemberDesc* md = td.getMember(t);
			printf("\t%s %s[", r.find(md->typeId)->getTypeName(), md->name.c_str());
			if (md->canRead()) {
				printf("gettable ");
			}
			if (md->canWrite()) {
				printf("settable");
			}
			printf("]\n");
		}
	}

	return 0;
}
