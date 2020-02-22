
#include "slib.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "PluginInterface.h"

enum TestEnum {
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

int main() {
	SLibType s;
	// s.foo();
	getTypeRegister().setPluginID(1);
	getTypeRegister().callRegisterTypesFunctions();

	auto& r = getTypeRegister();

	EvenBiggerContainer c;

	c.container.v.resize(5);
	c.container.v[3].a = te_1;

	MemberChain chain;
	chain.add(r.find(sgeTypeId(EvenBiggerContainer))->findMember("container", TypeId()));
	chain.add(r.find(sgeTypeId(Container))->findMember("v", TypeId()), 3);
	chain.add(r.find(sgeTypeId(Storage))->findMember("a", TypeId()));

	MemberAccessor ma = chain.follow(&c);

	TestEnum value = ma.get<TestEnum>().value();
	ma.set(te_2);

	HMODULE dllhmod = LoadLibraryA("dlib.dll");
	AllocatePluginInterfaceFnPtr allocInterfaceFnPtr = (AllocatePluginInterfaceFnPtr)GetProcAddress(dllhmod, "allocateInterface");

	IPluginInterface* plugin = allocInterfaceFnPtr();
	plugin->onLoad();
	plugin->updateTypes(getTypeRegister());
	getTypeRegister().obtainTypesFrom(plugin->getPluginTypeRegister());

	const TypeDesc* tdX = getTypeRegister().findByName("X");
	void* xVar = tdX->newFn();

	for (int t = 0; t < tdX->computeTotalNumMembers(); ++t) {
		const MemberDesc* md;
		void* xVarCasted = nullptr;
		tdX->getMemberInternal(xVar, t, md, &xVarCasted, nullptr);
		int v;
		md->callGetter(xVarCasted, &v);
		int breakPointHelper0 = 100;
	}

	chain.clear();
	chain.add(tdX->find1stMember("b"));
	int dllValue = chain.follow(xVar).get<int>().value();
	chain.follow(xVar).set(5000);
	dllValue = chain.follow(xVar).get<int>().value();

	for (auto tdItr : r.getAllTypes()) {
		auto td = tdItr.second;
		int numMembers = td.computeTotalNumMembers();
		printf("%s %d has these members:\n", td.getTypeName(), td.typeId.id);
		for (int t = 0; t < numMembers; ++t) {
			MemberAccessor m = td.getMember(nullptr, t);
			printf("\t%s %s[", r.find(m.md->typeId)->getTypeName(), m.md->name.c_str());
			if (m.md->canRead()) {
				printf("gettable ");
			}
			if (m.md->canWrite()) {
				printf("settable");
			}
			printf("]\n");
		}
	}

	return 0;
}
