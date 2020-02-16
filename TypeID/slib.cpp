#include "slib.h"
#include "typeid.h"

DefineTypeId(SLibType, 20'02'15'0001);
ReflRegisterBlock(SLibType)
{
	ReflAddType(SLibType)
		ReflMemberRaw(SLibType, "x", x);
}

int SLibType::foo() const {
	return x + 1;
}