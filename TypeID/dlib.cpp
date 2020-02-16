#include "typeid.h"

#include "PluginInterface.h"

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
struct DLLTypeToIntroduceSomeComplexity {
  int paddingValue = 76543;
  virtual const int &getValue() const = 0;
  virtual void setValue(const int &value) = 0;
};

struct DLLType : public DLLTypeToIntroduceSomeComplexity, public A {
  int dllValue = 707;
  DLLType() = default;
  const int &getValue() const { return dllValue; }
  void setValue(const int &value) { dllValue = value; }

  const int &getA() const override { return a; }
};
DefineTypeId(DLLType, 20'02'15'0002);
DefineTypeId(A, 20'02'15'0003);
ReflRegisterBlock(DLLType) {
  ReflAddType(A) ReflMember(A, int, "a", getA, setA);

  ReflAddType(DLLType) ReflInherits(DLLType, A)
      ReflMemberRaw(DLLType, "dllValue", dllValue);
  // ReflMember(DLLType, int, "dllValue", getValue, setValue);
}
//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
struct X : public DLLType, public B {
  virtual const int &getB() const override { return b; }
  void setB(const int &value) override { b = value; }
};

DefineTypeId(B, 20'02'15'0004);
DefineTypeId(X, 20'02'15'0005);
ReflRegisterBlock(X) {
  ReflAddType(B) ReflMember(B, int, "b", getB, setB);

  ReflAddType(X)
	  ReflInherits(X, DLLType)
	  ReflInherits(X, B);
}

//---------------------------------------------------------------------
// PluginInterface
//---------------------------------------------------------------------
class PluginInterface final : public IPluginInterface {

  ~PluginInterface() = default;

  virtual void onLoad() {
    new DLLType();
    getTypeRegister().setPluginID(1001);
  }

  void updateTypes(TypeRegister &somebodyElsesTypeRegister) final {
    getTypeRegister().obtainTypesFrom(somebodyElsesTypeRegister);
    getTypeRegister().callRegisterTypesFunctions();
  }

  TypeRegister &getPluginTypeRegister() final { return getTypeRegister(); }
};

extern "C" {
__declspec(dllexport) IPluginInterface *allocateInterface() {

  return new PluginInterface();
}
}
