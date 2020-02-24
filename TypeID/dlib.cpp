#include "typeid.h"

#include "PluginInterface.h"



//-------------------------------------------
//
//-------------------------------------------
struct A {
	virtual ~A() {
	}
	int a = 100;
	virtual const int& getA() const = 0;
	virtual void setA(const int& value) {
		a = value;
	}
};

struct B {
	virtual ~B() {
	}
	int b = 200;
	virtual const int& getB() const = 0;
	virtual void setB(const int& value) = 0;
};


//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
struct DLLTypeToIntroduceSomeComplexity {
	int paddingValue = 6000;
	virtual const int& getValue() const = 0;
	virtual void setValue(const int& value) = 0;
};

struct DLLType : public DLLTypeToIntroduceSomeComplexity, public A {
	int dllValue = 707;
	DLLType() = default;
	const int& getValue() const {
		return dllValue;
	}
	void setValue(const int& value) {
		dllValue = value;
	}

	const int& getA() const override {
		return a;
	}
};
DefineTypeId(DLLType, 20'02'15'0002);
DefineTypeId(A, 20'02'15'0003);
ReflRegisterBlock(DLLType) {
	ReflAddType(A) ReflMember(A, int, "a", getA, setA);

	ReflAddType(DLLType) ReflInherits(DLLType, A) ReflMemberRaw(DLLType, "dllValue", dllValue);
	// ReflMember(DLLType, int, "dllValue", getValue, setValue);
}
//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
struct X : public DLLType, public B {
	virtual const int& getB() const override {
		return b;
	}
	void setB(const int& value) override {
		b = value;
	}
};

DefineTypeId(B, 20'02'15'0004);
DefineTypeId(X, 20'02'15'0005);
ReflRegisterBlock(X) {
	ReflAddType(B) ReflMember(B, int, "b", getB, setB);

	ReflAddType(X) ReflInherits(X, DLLType) ReflInherits(X, B);
}

//---------------------------------------------------------------------
// PluginInterface
//---------------------------------------------------------------------
class PluginInterface final : public IPluginInterface {
	~PluginInterface() = default;

	virtual void onLoad() {
		new DLLType();
		typeLib().setPluginID(1001);
	}

	void updateTypes(TypeLibrary& somebodyElsesTypeRegister) final {
		typeLib().obtainTypesFrom(somebodyElsesTypeRegister);
		typeLib().doRegisteration();
	}

	TypeLibrary& getPluginTypeRegister() final {
		return typeLib();
	}
};

#ifdef _WIN32
#define SgeExport __declspec(dllexport)
#else
#define SgeExport __attribute__((visibility("default")))
#endif

extern "C" {
SgeExport IPluginInterface* allocateInterface() {
	return new PluginInterface();
}
}
