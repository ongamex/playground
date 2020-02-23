#pragma once

#include "typeid.h"

struct IPluginInterface {
	virtual ~IPluginInterface() {
	}

	virtual void onLoad() = 0;
	virtual void updateTypes(TypeRegister& somebodyElsesTypeRegister) = 0;
	virtual TypeRegister& getPluginTypeRegister() = 0;
};

typedef IPluginInterface* (*AllocatePluginInterfaceFnPtr)();
