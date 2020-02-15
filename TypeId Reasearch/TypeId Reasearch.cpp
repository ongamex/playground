
#include "CommonTypes.h"
#include <iostream>

enum TestEnum {
  te_0,
  te_1,
  te_2,
};

struct Storage {
  int z = 0;
  TestEnum a = te_0;

public:
  const TestEnum &getA() const { return a; }
  void setA(const TestEnum &_) { a = _; }
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
  ReflDefineType(TestEnum) ReflEnumVal(te_0, "te_0") ReflEnumVal(te_1, "te_1")
      ReflEnumVal(te_2, "te_2");

  ReflDefineType(Container) ReflMemberRaw(Container, "v", v);

  ReflDefineType(std::vector<Storage>);
  ReflDefineType(Storage) ReflMemberRaw(Storage, "z", z)
      ReflMember(Storage, TestEnum, "a", getA, setA);

  ReflDefineType(EvenBiggerContainer)
      ReflMemberRaw(EvenBiggerContainer, "container", container);
}

int main() {

  getTypeRegister().callRegisterTypesFunctions();

  auto &r = getTypeRegister();

  EvenBiggerContainer c;

  c.container.v.resize(5);
  c.container.v[3].a = te_1;

  MemberChain chain;
  chain.add(r.find(sgeTypeId(EvenBiggerContainer))
                ->findMember("container", TypeId()));
  chain.add(r.find(sgeTypeId(Container))->findMember("v", TypeId()), 3);
  chain.add(r.find(sgeTypeId(Storage))->findMember("a", TypeId()));

  MemberAccessor ma = chain.follow(&c);

  TestEnum value = ma.get<TestEnum>().value();
  ma.set(te_2);

  for (auto tdItr : r.getAllTypes()) {
    auto td = tdItr.second;
    int numMembers = td.computeTotalNumMembers();
    printf("%s has these members:\n", td.getTypeName());
    for (int t = 0; t < numMembers; ++t) {
      MemberAccessor m = td.getMember(nullptr, t);
      printf("\t%s %s[", r.find(m.md->typeId)->getTypeName(),
             m.md->name.c_str());
      if (m.md->getter != nullptr) {
        printf("gettable ");
      }
      if (m.md->setter != nullptr) {
        printf("settable");
      }
      printf("]\n");
    }
  }

  return 0;
}
