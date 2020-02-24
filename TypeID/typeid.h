#pragma once

#include <assert.h>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#define SGE_CAT_IMPL(s1, s2) s1##s2
#define SGE_CAT(s1, s2) SGE_CAT_IMPL(s1, s2)
#define SGE_ANONYMOUS(x) SGE_CAT(x, __COUNTER__)

struct TypeId {
	int id;

	explicit TypeId(int const id = 0)
	    : id(id) {
	}
	bool isNull() const {
		return id == 0;
	}

	bool operator<(const TypeId& r) const {
		return id < r.id;
	}
	bool operator>(const TypeId& r) const {
		return id > r.id;
	}
	bool operator==(const TypeId& r) const {
		return id == r.id;
	}
	bool operator!=(const TypeId& r) const {
		return id != r.id;
	}
};


/// Definition of std::hash<TypeId>
namespace std {
template <>
struct hash<TypeId> {
	int operator()(const TypeId& k) const {
		return k.id;
	}
};
} // namespace std


/// A funtion providing the type-id of each type.
/// A function specialization for everytype that participates in the reflection
/// must be provided. If you get linker errors it is because this function isn't
/// defined for a type that is used in the reflection system.
/// 0 is reserved for invalid id.
///
/// A good nomenclature for assigning ids is:
/// yy'mm'dd'nnnn where nnnn is the number of type registered on this day.
template <typename T>
TypeId sgeTypeIdFn();

/// Don't use in header definition it will bloat the cpps with useless
/// stuff.
//#define DefineTypeIdInline(T, _id) \
//  template <> inline TypeId sgeTypeIdFn<T>() { return TypeId(_id); }

#define DefineTypeId(T, _id)  \
	template <>               \
	TypeId sgeTypeIdFn<T>() { \
		return TypeId(_id);   \
	}

/// A macros used to quckly obtain id for a particular type.
#define sgeTypeId(T) sgeTypeIdFn<T>()

//---------------------------------------------------
//
//---------------------------------------------------
template <class T>
struct sge_remove_cvref {
	typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template <typename T>
struct is_compareable {
	struct yes {
		char a[1];
	};
	struct no {
		char a[2];
	};

	template <typename C>
	static yes test_eq(decltype(&C::operator==));
	template <typename C>
	static no test_eq(...);

	template <typename C>
	static yes test_neq(decltype(&C::operator!=));
	template <typename C>
	static no test_neq(...);

	enum { value = (sizeof(test_eq<T>(0)) == sizeof(yes) && sizeof(test_neq<T>(0)) == sizeof(yes)) };
};

template <typename T, typename M>
constexpr int sge_offsetof(M T::*member) {
	return (int)((char*)&((T*)nullptr->*member) - (char*)nullptr);
}

template <typename Test, template <typename...> class Ref>
struct is_specialization : std::false_type {};

template <template <typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

///-------------------------------------------------------------------------------------------
///
///-------------------------------------------------------------------------------------------
struct TypeLibrary;

/// typeLib() is a function used to access the global type register for the current binary.
TypeLibrary& typeLib();

///-------------------------------------------------------------------------------------------
/// MemberDesc
///
/// A structure storing the user-specified data for a member of a type.
///-------------------------------------------------------------------------------------------
typedef void* (*CastFn)(void* from);

struct TypeDesc;
struct MemberDesc {
	friend TypeDesc;

	const TypeDesc* owningTypeDesc = nullptr;
	TypeId typeId;
	std::string name;

	int userLookUpNumber = 0;

  private:
	// An array storing all the necesary casts from the type described by owningTypeDesc
	// to the type that can correctly proivde the specified member.
	std::vector<CastFn> castFromOwnerToCorretTypeChain;

	void (*getter)(void* object, void* dest) = nullptr;
	void (*setter)(void* object, const void* src) = nullptr;

  public:
	bool canRead() const {
		return getter != nullptr;
	}
	bool canWrite() const {
		return setter != nullptr;
	}

	/// Cast the specified pointer, assumed to be of type described by owningType
	/// to the correct type. that provides this member.
	/// For example if the member is inherited owner != retval.
	void* castOwner(void* object) const;

	/// Invokes the specified getter assuming that the provided object
	/// is of type described by owningType.
	void callGetter(void* object, void* const dest) const {
		assert(object && dest);
		object = castOwner(object);
		getter(object, dest);
	}

	/// Invokes the specified setter assuming that the provided object
	/// is of type described by owningType.
	void callSetter(void* object, const void* const src) const {
		assert(object && src);
		object = castOwner(object);
		setter(object, src);
	}

	/// Invokes the specified getter assuming that the provided objectCasted
	/// is already casted to the correct type.
	void callGetterNoCast(void* const objectCasted, void* const dest) const {
		assert(objectCasted && dest);
		getter(objectCasted, dest);
	}

	/// Invokes the specified setter assuming that the provided objectCasted
	/// is already casted to the correct type.
	void callSetterNoCast(void* const objectCasted, const void* const src) const {
		assert(objectCasted && src);
		setter(objectCasted, src);
	}
};

///-------------------------------------------------------------------------------------------
/// TypeDesc
///
/// A structure holding the user-specified reflection data for a type.
///-------------------------------------------------------------------------------------------
struct TypeDesc {
	friend struct TypeLibrary;

  public:
	struct ParentClassData {
		TypeId parentClassId;
		void* (*castToParent)(void* object) = nullptr;
	};

  public:
	/// The id of the plugin (exe/dll/so) that registered that type.
	int providingPluginId;
	TypeId typeId;
	std::string typeName;
	std::vector<ParentClassData> parentClasses;
	std::vector<MemberDesc> members;

	// Constructors, destructors and non-array allocation.
	void (*constructorFn)(void* dest) = nullptr;
	void (*destructorFn)(void* dest) = nullptr;
	void* (*newFn)() = nullptr;
	void (*deleteFn)(void* ptr) = nullptr;

	// Copy-assign.
	void (*copyFn)(void* dest, const void* src) = nullptr;

	// Comparison.
	bool (*equalsFn)(const void* a, const void* b) = nullptr;

	// Enums
	TypeId enumUnderlayingType;
	std::unordered_map<int, std::string> enumValueToNameLUT;

	// std::vector functions.
	TypeId stdVectorUnderlayingType;
	size_t (*stdVectorSize)(const void* vector) = nullptr;
	void (*stdVectorEraseAtIndex)(void* vector, size_t index) = nullptr;
	void (*stdVectorResize)(void* vector, size_t size) = nullptr;
	void* (*stdVectorGetElement)(void* vector, size_t index) = nullptr;
	const void* (*stdVectorGetElementConst)(const void* vector, size_t index) = nullptr;

  public:
	/// Retrieves the total number of members described, including the once inherited.
	int numMembers() const {
		int memberCnt = int(members.size());
		return memberCnt;
	}

	/// Retrieves the i-th member desc of the type. This includes the members
	/// of the parent types.
	/// @param[in] rootObject a pointer to the root object that is later going to
	/// be cased to the correct type so member get/set functions could be called.
	///                       ignored if nullptr.
	/// @param[in] iMember the index of the member to be obtained. goes form 0 to
	/// numMembers().
	/// @param[out] outMemberDesc will contain the description of the requested
	/// member.
	/// @result rootObject casted to the correct type, enabling calling get/set to
	/// be vaild.
	const MemberDesc* getMember(const int iMember) const;

	/// Finds the 1st member with the specified name.
	const MemberDesc* find1stMember(const char* const name) const;

	/// Marks that this type inherits the specified TParent class.
	/// The declaration is statically checked with an assert, if the type
	/// does not inherit TParent the compilation should fail.
	template <typename T, typename TParent>
	TypeDesc& inherits() {
		static_assert(std::is_base_of<TParent, T>::value, "T must inherit TParent");
		ParentClassData pd;

		pd.parentClassId = sgeTypeIdFn<TParent>();
		pd.castToParent = [](void* object) -> void* {
			T* const objTyped = reinterpret_cast<T*>(object);
			TParent* const objAsParent = static_cast<TParent*>(objTyped);
			void* const objAsParentVoid = reinterpret_cast<void*>(objAsParent);
			return objAsParentVoid;
		};

		parentClasses.push_back(pd);

		const TypeDesc* const tdParentClass = typeLib().find(pd.parentClassId);

		if (tdParentClass) {
			for (const MemberDesc& md : tdParentClass->members) {
				MemberDesc copiedMember = md;
				copiedMember.castFromOwnerToCorretTypeChain.insert(copiedMember.castFromOwnerToCorretTypeChain.begin(), pd.castToParent);
				members.emplace_back(std::move(copiedMember));
			}
		}

		return *this;
	}

	/// Declares a direct member of this type, which is just a member-variable,
	/// That doesn't have explicit get and set methods.
	/// The member must be public.
	/// This function will generates it own get() set() functions to be used.
	template <typename T, typename M, M T::*memberPtr>
	TypeDesc& addMemberRaw(const char* name) {
		const auto getter = [](void* object, void* dest) -> void {
			int byteOffsetDesc = sge_offsetof(memberPtr);
			char* memberLoc = (char*)(object) + byteOffsetDesc;
			const M& memberRef = *(const M*)memberLoc;
			M& output = *(M*)dest;
			output = memberRef;
		};

		const auto setter = [](void* object, const void* src) -> void {
			int byteOffsetDesc = sge_offsetof(memberPtr);
			char* memberLoc = (char*)(object) + byteOffsetDesc;
			M& memberRef = *(M*)memberLoc;
			const M& input = *(const M*)src;
			memberRef = input;
		};

		MemberDesc member;
		member.owningTypeDesc = this;
		member.name = name;
		member.typeId = sgeTypeId(M);
		member.getter = getter;
		member.setter = setter;

		members.emplace_back(std::move(member));
		return *this;
	}

	/// Declares a direct member of this type
	/// That is going to be acessed by the specified getter, no setter available.
	template <typename T, typename M, const M& (T::*getter)() const>
	TypeDesc& addMemberWithGetNoSetter(const char* name) {
		auto getDataFn = [](void* object, void* dest) -> void { *((M*)(dest)) = (((T*)(object))->*getter)(); };

		MemberDesc member;
		member.owningTypeDesc = this;
		member.name = name;
		member.typeId = sgeTypeId(M);
		member.getter = getDataFn;
		member.setter = nullptr;

		members.emplace_back(std::move(member));
		return *this;
	}

	/// Declares a direct member of this type
	/// That is going to be acessed by the specified getter and setter functions.
	template <typename T, typename M, const M& (T::*getter)() const, void (T::*setter)(const M&)>
	TypeDesc& addMemberWithGetSet(const char* name) {
		auto getDataFn = [](void* object, void* dest) -> void { *((M*)(dest)) = (((T*)(object))->*getter)(); };
		auto setDataFn = [](void* object, const void* src) -> void { (((T*)(object))->*setter)(*((M*)(src))); };

		MemberDesc member;
		member.owningTypeDesc = this;
		member.name = name;
		member.typeId = sgeTypeIdFn<M>();
		member.getter = getDataFn;
		member.setter = setDataFn;

		members.emplace_back(std::move(member));
		return *this;
	}

	/// Register a possible value for an enum
	TypeDesc& addEnumMember(int enumMember, const char* const name);

	const char* const getTypeName() const {
		return typeName.c_str();
	}
};

///-------------------------------------------------------------------------------------------
/// TypeLibrary
///
/// A global strcture, storing all reflected types.
/// TypeDesc and MemberDesc will refer to this global register and quering
/// information about other types.
///-------------------------------------------------------------------------------------------
struct TypeLibrary {
	friend int addFunctionThatDefinesTypesToTypeLibrary(void (*fnPtr)());

	TypeLibrary() = default;
	TypeLibrary(const TypeLibrary&) = delete;
	TypeLibrary& operator=(const TypeLibrary&) = delete;

	/// This function initiates the registration of all types.
	/// Once finished, the reflection system is ready to be used.
	void doRegisteration();

	/// Drains all the missing types coming form the other type register.
	/// Used when multiple binaries need to keep track of the same types.
	void obtainTypesFrom(TypeLibrary& other);

	template <class T>
	TypeDesc& addType(const char* const typeName) {
		if (getPluginID() == 0) {
			// Check if a plugin id was set, this id is needed when a plugin is
			// reloaded while the engine is running, old types form this plugins need
			// to be deleted and then added again once the plugin is again loaded.
			// this pluginID is used to identify the types that need to be deleted.

			// Return a dummy typedesc that isn't going to be actually used,
			// we are just making the compiler happy.
			static TypeDesc tdDummyForFaultyPluginIds;
			tdDummyForFaultyPluginIds = TypeDesc();
			assert(false &&
			       "Please set some id for the current exe/dll before "
			       "registering any types! see setPluginID(). This type "
			       "won't get regstered");
			return tdDummyForFaultyPluginIds;
		}

		TypeId id = sgeTypeIdFn<T>();

		// Check if the type is already registered.
		if (types.count(id) != 0) {
			// If the type has already been registered by another pluging, do not warn
			// as these types are usually int,float,string and so on.
			// TODO: Add a check that bypasses these types and checks for everything
			// else.
			if (types[id].providingPluginId == getPluginID()) {
				assert(false && "A type with the same id has already been registered!");
			}

			// Return a dummy typedesc that isn't going to be actually used,
			// we are just making the compiler happy.
			static TypeDesc tdDummyForFaultyTypeIds;
			tdDummyForFaultyTypeIds = TypeDesc();
			return tdDummyForFaultyTypeIds;
		}

		TypeDesc& td = types[id];

		td.providingPluginId = getPluginID();
		td.typeId = id;
		td.typeName = typeName;

		// Check if the type is constructable.
		if constexpr (std::is_default_constructible<T>::value) {
			td.constructorFn = [](void* dest) { new ((T*)dest) T(); };
			td.destructorFn = [](void* dest) { ((T*)dest)->~T(); };
			td.newFn = []() -> void* { return new T(); };
			td.deleteFn = [](void* ptr) -> void {
				if (ptr) {
					delete ((T*)ptr);
				}
			};
		}

		// Copy and assign.
		if constexpr (std::is_copy_assignable<T>::value) {
			td.copyFn = [](void* dest, const void* src) { *(T*)(dest) = *(T*)(src); };
		}

		// Comparison
		if constexpr (is_compareable<T>::value) {
			td.equalsFn = [](const void* a, const void* b) -> bool { return *(T*)(a) == *(T*)(b); };
		}

		// Check if the type is an enum.
		if constexpr (std::is_enum<T>::value) {
			td.enumUnderlayingType = sgeTypeId(typename std::underlying_type<T>::type);
		}

		// Check if the type is a specialization of a std::vector,
		// if so save a few function that the user might be interested.
		if constexpr (is_specialization<T, std::vector>::value) {
			td.stdVectorUnderlayingType = sgeTypeId(typename T::value_type);

			td.stdVectorSize = [](const void* vector) -> size_t { return (*(T*)(vector)).size(); };

			td.stdVectorEraseAtIndex = [](void* vector, size_t index) -> void {
				auto& v = *(T*)(vector);
				v.erase(v.begin() + index);
			};

			td.stdVectorResize = [](void* vector, size_t size) -> void { (*(T*)(vector)).resize(size); };
			td.stdVectorGetElement = [](void* vector, size_t index) -> void* { return &(*(T*)(vector))[index]; };
			td.stdVectorGetElementConst = [](const void* vector, size_t index) -> const void* { return &(*(T*)(vector))[index]; };
		}

		return td;
	}

	const TypeDesc* find(const TypeId id) const;
	const TypeDesc* findByName(const char* const) const;

	const std::unordered_map<TypeId, TypeDesc>& getAllTypes() const {
		return types;
	}

	int getPluginID() const {
		return pluginID;
	}

	void setPluginID(int id) {
		pluginID = id;
	}

  private:
	std::unordered_map<TypeId, TypeDesc> types;
	std::vector<void (*)()> functionsToBeCalledThatWillRegisterTypes;
	int pluginID = 0;
};

int addFunctionThatDefinesTypesToTypeLibrary(void (*fnPtr)());

///-------------------------------------------------------------------------------------------
/// A set of helper macros, used to create type definitions (TypeDesc).
///-------------------------------------------------------------------------------------------

/// Starts a definition of a type.
#define ReflAddType(T) typeLib().addType<T>(#T)

#define ReflInherits(T, TParent) .inherits<T, TParent>()

/// Adds a reflection describing a member-variable which will have automatically
/// generate get and get functions
#define ReflMemberRaw(T, memberName, member) .addMemberRaw<T, decltype(T::member), &T::member>(memberName)

/// Adds a reflection describing a member-variable which will be read
/// with the provided getter, no setting available.
#define ReflMemberNoSetter(T, TMemberType, memberName, getter) .addMemberWithGetNoSetter<T, TMemberType, &T::getter>(memberName)

/// Adds a reflection describing a member-variable which will be acessed
/// with the provided get and set methods.
#define ReflMember(T, TMemberType, memberName, getter, setter) .addMemberWithGetSet<T, TMemberType, &T::getter, &T::setter>(memberName)

#define ReflMemberSetterOnly(T, TMemberType, memberName, getter, setter) .addMemberWithGet<T, TMemberType, &T::getter>(memberName)

#define ReflEnumVal(v, name) .addEnumMember(int(v), name)

///-------------------------------------------------------------------------------------------
/// A set of macros that enable the user to declare reflection inside a header
/// or a cpp file. The registration will happen when
/// TypeLibrary::doRegisteration() is called.
///-------------------------------------------------------------------------------------------
#define ReflRegisterBlock(comment) ReflRegisterBlock_Impl(SGE_ANONYMOUS(_SGE_REFL_ANON__FUNC))

#define ReflRegisterBlock_Impl(fnName)                                                                    \
	static void fnName();                                                                                 \
	static int SGE_ANONYMOUS(fnNameRegisterVariable) = addFunctionThatDefinesTypesToTypeLibrary(&fnName); \
	static void fnName()

///-------------------------------------------------------------------------------------------
/// Member chain.
/// TODO:
/// this won't work with realoadable dlls as when reloading, the previous
/// pointers will get invalidated. Which will break the UNDO/REDO which is based
/// on this reflection. As a workaround we can delete the histroy or not use
/// MemberDesc pointers but something else:
/// for example name+typeid+index, to ensure that this is the same member.
///-------------------------------------------------------------------------------------------

struct MemberAccessor;

struct MemberChain {
	struct Knot {
		Knot(const MemberDesc* const md = nullptr, const int arrayIndex = -1)
		    : md(md)
		    , arrayIndex(arrayIndex) {
		}

		const MemberDesc* md = nullptr;
		int arrayIndex = -1; // -1 identifies that indexing is going to be actually used.
	};

  public:
	bool add(const MemberDesc* mfd, int idx = -1);

	void pop();
	void clear();

	MemberAccessor follow(void* root) const;

  private:
	std::vector<Knot> knots;
};

/// MemberAccessor provides a convinent and typesafe method for acessing values from a MemberDesc.
struct MemberAccessor {
	const MemberDesc* md;
	void* properlyCastedOwner;

	MemberAccessor(const MemberDesc* const md = nullptr, void* const properlyCastedOwner = nullptr)
	    : md(md)
	    , properlyCastedOwner(properlyCastedOwner) {
	}

	bool canRead() const {
		bool result = properlyCastedOwner != nullptr && md != nullptr && md->canRead();
		return result;
	}

	bool canWrite() const {
		bool result = properlyCastedOwner != nullptr && md != nullptr && md->canWrite();
		return result;
	}

	template <typename T>
	std::optional<T> get() const {
		if (canRead() && md->typeId == sgeTypeId(T)) {
			T result;
			md->callGetterNoCast(properlyCastedOwner, &result);
			return std::move(result);
		}

		assert(false);
		return std::nullopt;
	}

	template <typename T>
	bool set(const T& value) const {
		if (canWrite() && sgeTypeId(T) == md->typeId) {
			md->callSetterNoCast(properlyCastedOwner, &value);
			return true;
		}

		assert(false);
		return false;
	}
};
