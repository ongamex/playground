#pragma once

#include "typeid.h"
#include <set>
#include <string>

//---------------------------------------------------
//
//---------------------------------------------------
struct Actor {
  virtual ~Actor() = default;
  virtual void update() = 0;

  const int &getId() const { return id; }

private:
  int id;
};


//---------------------------------------------------
//
//---------------------------------------------------
struct Player : public Actor {
  virtual void update() override {}

  float health = 100.f;
};



// template<> int id<vec3>();
// template <> struct GetTypeId<vec3>;
