#pragma once

#include "typeid.h"

struct IPluginInterface {
  virtual ~IPluginInterface() {}

  virtual void onLoad() = 0;
  virtual void updateTypes(TypeRegister &somebodyElsesTypeRegister) = 0;
  virtual TypeRegister &getPluginTypeRegister() = 0;
};

typedef IPluginInterface *(*AllocatePluginInterfaceFnPtr)();

//-------------------------------------------
//
//-------------------------------------------
struct A {
  virtual ~A() {}
  int a = 100;
  virtual const int &getA() const = 0;
  virtual void setA(const int &value) { a = value; }
};

struct B {
  virtual ~B() {}
  int b = 200;
  virtual const int &getB() const = 0;
  virtual void setB(const int &value) = 0;
};
