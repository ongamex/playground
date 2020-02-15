#include "CommonTypes.h"
#include "typeid.h"

DefineTypeId(Actor, 20'02'09'0001);
ReflRegisterBlock("Actor") {
  // clang-format off
  ReflDefineType(Actor)
    ReflMemberNoSetter(Actor, int, "id", getId)
  ;
  // clang-format on
}


DefineTypeId(Player, 20'02'09'0002);
ReflRegisterBlock("Player") {
  // clang-format off
  ReflDefineType(Player)
    ReflInherits(Player, Actor)
    ReflMemberRaw(Player, "health", health)
  ;
  // clang-format on
}