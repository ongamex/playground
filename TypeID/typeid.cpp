#include "typeid.h"
#include <assert.h>

TypeRegister& getTypeRegister() {
	static TypeRegister s;
	return s;
}

void* MemberDesc::castOwner(void* object) const {
	// TODO: Optimize this! It should be doable without a search.
	int numCasts = int(castFromOwnerToCorretTypeChain.size());
	for (int t = 0; t < numCasts; ++t) {
		object = castFromOwnerToCorretTypeChain[t](object);
	}

	return object;
}

void TypeRegister::obtainTypesFrom(TypeRegister& other) {
	for (const auto& otherPair : other.types) {
		const TypeDesc* const existingTypeDescInThis = find(otherPair.first);
		if (existingTypeDescInThis == nullptr) {
			// A new type is found. Copy it's descriptor.
			types[otherPair.first] = otherPair.second;
		} else {
			// Just some asserts that do not prove 100% compatibility between the
			// externally registered type and the pre-existing one in our type
			// register but it is some way to find mismatches.
			// TODO: Add a better check for mismatched types.
			assert(existingTypeDescInThis->typeName == otherPair.second.typeName);
			assert(existingTypeDescInThis->typeId == otherPair.second.typeId);
		}
	}
}

const TypeDesc* TypeRegister::find(const TypeId id) const {
	auto itr = types.find(id);
	if (itr != types.end()) {
		return &itr->second;
	}

	return nullptr;
}

const TypeDesc* TypeRegister::findByName(const char* const name) const {
	for (const auto& pair : types) {
		if (pair.second.typeName == name) {
			return &pair.second;
		}
	}

	return nullptr;
}

int TypeDesc::computeTotalNumMembers() const {
	int memberCnt = int(members.size());
	return memberCnt;
}

void TypeDesc::getMemberInternal(void* rootObject,
                                 const int iMember,
                                 const MemberDesc*& outMemberDesc,
                                 void** outRootCasted,
                                 TypeId* const outClassProvidingMember) const {
	outMemberDesc = nullptr;
	if (outRootCasted) {
		*outRootCasted = nullptr;
	}

	/// Check if the member is not inherited, if so then no need to do the loop
	/// below.
	if (iMember < int(members.size())) {
		outMemberDesc = &members[iMember];
		if (outRootCasted) {
			*outRootCasted = outMemberDesc->castOwner(rootObject);
		}
		if (outClassProvidingMember) {
			*outClassProvidingMember = this->typeId;
		}
		return;
	}

	return;
}

const MemberDesc* TypeDesc::find1stMember(const char* const name) const {
	const MemberDesc* result = nullptr;
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

const MemberDesc* TypeDesc::findMember(const char* const name, TypeId typeProvidingMember) const {
	if (typeProvidingMember.isNull()) {
		typeProvidingMember = this->typeId;
	}
	const MemberDesc* result = nullptr;
	int numMembers = computeTotalNumMembers();
	for (int t = 0; t < numMembers; ++t) {
		TypeId typeProvidingThisMember;
		getMemberInternal(nullptr, t, result, nullptr, &typeProvidingThisMember);
		if (typeProvidingMember == typeProvidingThisMember && result->name == name) {
			return result;
		}
	}

	assert(false && "Searching for a member that doesn't exists!");
	return result;
}

TypeDesc& TypeDesc::addEnumMember(int enumMember, const char* const name) {
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
	for (auto& fn : functionsToBeCalledThatWillRegisterTypes) {
		fn();
	}
}

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
bool MemberChain::add(const MemberDesc* md, int idx) {
	if (!md) {
		assert(false);
		return false;
	}

	knots.emplace_back(Knot(md, idx));
	return true;
}

void MemberChain::pop() {
	knots.pop_back();
}

void MemberChain::clear() {
	knots.clear();
}

MemberAccessor MemberChain::follow(void* root) const {
	void* outMemberOwner = nullptr;

	void* prevMemberOwner = root;
	for (const auto& knot : knots) {
		if (knot.arrayIndex < 0) {
			outMemberOwner = knot.md->castOwner(prevMemberOwner);
			prevMemberOwner = root;
		} else {
			outMemberOwner = knot.md->castOwner(prevMemberOwner);
			const TypeDesc* knotVectorTypeDesc = getTypeRegister().find(knot.md->typeId);
			if (knotVectorTypeDesc) {
				outMemberOwner = knotVectorTypeDesc->stdVectorGetElement(outMemberOwner, knot.arrayIndex);
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
DefineTypeId(unsigned int, 00'00'00'0002);
DefineTypeId(float, 00'00'00'0003);
DefineTypeId(std::string, 00'00'00'0004);

ReflRegisterBlock(Basic Types) {
	ReflAddType(int);
	ReflAddType(float);
	ReflAddType(std::string);
}
