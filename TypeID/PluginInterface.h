#pragma once

#include "typeid.h"

struct IPluginInterface {
	virtual ~IPluginInterface() {
	}

	virtual void onLoad() = 0;
	virtual void updateTypes(TypeLibrary& somebodyElsesTypeRegister) = 0;
	virtual TypeLibrary& getPluginTypeRegister() = 0;
};

typedef IPluginInterface* (*AllocatePluginInterfaceFnPtr)();
