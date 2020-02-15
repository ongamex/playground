#include "typeid.h"
#include <assert.h>

TypeRegister &getTypeRegister() {
  static TypeRegister s;
  return s;
}

void *MemberDesc::castOwner(void *owner) const {
  // TODO: Optimize this! It should be doable without a search.
  int numMembersInOwner = this->owner->computeTotalNumMembers();
  for (int t = 0; t < numMembersInOwner; ++t) {
    MemberAccessor memAcc = this->owner->getMember(owner, t);
    if (memAcc.md == this) {
      return memAcc.owner;
    }
  }

  assert(false && "Searching for a member that should exists!");
  return nullptr;
}

const TypeDesc *TypeRegister::find(const TypeId id) const {

  auto itr = types.find(id);
  if (itr != types.end()) {
    return &itr->second;
  }

  return nullptr;
}

int TypeDesc::computeTotalNumMembers() const {
  int memberCnt = members.size();

  TypeRegister &r = getTypeRegister();
  for (int t = 0; t < int(parentClasses.size()); ++t) {
    const TypeDesc *parentTypeDesc = r.find(parentClasses[t].parentClassId);
    if (parentTypeDesc != nullptr) {
      memberCnt += parentTypeDesc->computeTotalNumMembers();
    }
  }

  return memberCnt;
}

void TypeDesc::getMemberInternal(void *rootObject, const int iMember,
                                 const MemberDesc *&outMemberDesc,
                                 void **outRootCasted,
                                 TypeId *const outClassProvidingMember) const {

  outMemberDesc = nullptr;
  if (outRootCasted) {
    *outRootCasted = nullptr;
  }

  /// Check if the member is not inherited, if so then no need to do the loop
  /// below.
  if (iMember < int(members.size())) {
    outMemberDesc = &members[iMember];
    if (outRootCasted) {
      *outRootCasted = rootObject;
    }
    if (outClassProvidingMember) {
      *outClassProvidingMember = this->typeId;
    }
    return;
  }

  // The asked member does not reside the the type itself, so it must be
  // somewhere in the inherited types.
  int memberParentLocalIdx = iMember - int(members.size());
  for (int t = 0; t < int(parentClasses.size()); ++t) {
    assert(memberParentLocalIdx >= 0);
    const TypeDesc *parentTypeDesc =
        getTypeRegister().find(parentClasses[t].parentClassId);

    if (parentTypeDesc == nullptr) {
      assert(false &&
             "Using a un-reflected type as a parent of reflected type! The "
             "code will continue to work correctly, skipping it, however you "
             "probably want to add reflection for this type");
      continue;
    }

    const int totalMemberInParent = parentTypeDesc->computeTotalNumMembers();
    if (memberParentLocalIdx >= totalMemberInParent) {
      // The member is beyond that parent, try with the next one.
      memberParentLocalIdx -= totalMemberInParent;
    } else {
      // The member is in this parent type.
      void *rootObjAsParentType =
          rootObject ? parentClasses[t].castToParent(rootObject) : nullptr;
      parentTypeDesc->getMemberInternal(rootObjAsParentType,
                                        memberParentLocalIdx, outMemberDesc,
                                        outRootCasted, outClassProvidingMember);
      return;
    }
  }

  assert(false);

  outMemberDesc = nullptr;
  if (outRootCasted) {
    outRootCasted = nullptr;
  }
  return;
}

const MemberDesc *TypeDesc::find1stMember(const char *const name) const {

  const MemberDesc *result = nullptr;
  int numMembers = computeTotalNumMembers();
  for (int t = 0; t < numMembers; ++t) {
    getMemberInternal(nullptr, t, result, nullptr);
    if (result->name == name) {
      return result;
    }
  }

  assert(false && "Searching for a member that doesn't exists!");
  return result;
}

const MemberDesc *TypeDesc::findMember(const char *const name,
                                       TypeId typeProvidingMember) const {
  if (typeProvidingMember.isNull()) {
    typeProvidingMember = this->typeId;
  }
  const MemberDesc *result = nullptr;
  int numMembers = computeTotalNumMembers();
  for (int t = 0; t < numMembers; ++t) {
    TypeId typeProvidingThisMember;
    getMemberInternal(nullptr, t, result, nullptr, &typeProvidingThisMember);
    if (typeProvidingMember == typeProvidingThisMember &&
        result->name == name) {
      return result;
    }
  }

  assert(false && "Searching for a member that doesn't exists!");
  return result;
}

TypeDesc &TypeDesc::addEnumMember(int enumMember, const char *const name) {
  if (enumUnderlayingType.isNull() == false) {
    if (enumValueToNameLUT.count(enumMember) == 0) {
      enumValueToNameLUT[enumMember] = std::string(name);
    } else {
      assert(false);
    }
  } else {
    assert(false);
  }

  return *this;
}

int addFunctionThatDefinesTypesToTypeRegister(void (*fnPtr)()) {
  getTypeRegister().functionsToBeCalledThatWillRegisterTypes.insert(fnPtr);
  return 0;
}

void TypeRegister::callRegisterTypesFunctions() {
  for (auto &fn : functionsToBeCalledThatWillRegisterTypes) {
    fn();
  }
}

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
bool MemberChain::add(const MemberDesc *mfd, int idx) {
  if (!mfd) {
    assert(false);
    return false;
  }

  knots.emplace_back(Knot(mfd, idx));
  return true;
}

void MemberChain::pop() { knots.pop_back(); }

void MemberChain::clear() { knots.clear(); }

MemberAccessor MemberChain::follow(void *root) const {
  void *outMemberOwner = nullptr;

  void *prevMemberOwner = root;
  for (const auto &knot : knots) {
    if (knot.arrayIndex < 0) {
      outMemberOwner = knot.md->castOwner(prevMemberOwner);
      prevMemberOwner = root;
    } else {
      outMemberOwner = knot.md->castOwner(prevMemberOwner);
      const TypeDesc *knotVectorTypeDesc =
          getTypeRegister().find(knot.md->typeId);
      if (knotVectorTypeDesc) {
        outMemberOwner = knotVectorTypeDesc->stdVectorGetElement(
            outMemberOwner, knot.arrayIndex);
        prevMemberOwner = outMemberOwner;
      } else {
        assert(false && "Broken link expected indexable type!");
        outMemberOwner = nullptr;
        return MemberAccessor();
      }
    }
  }

  return MemberAccessor(knots.back().md, outMemberOwner);
}

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
// DefineTypeId(TypeId, 00'00'00'0001); todo: make TypeId not a typedef
DefineTypeId(int, 00'00'00'0001);
DefineTypeId(float, 00'00'00'0002);
DefineTypeId(std::string, 00'00'00'0003);

ReflRegisterBlock(Basic Types) {
  ReflDefineType(int);
  ReflDefineType(float);
  ReflDefineType(std::string);
}
