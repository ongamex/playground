#pragma once

#include <string>

struct Ast;

template <int Nbytes>
struct Variant
{
	Variant() : bObjectValid(false) {}

	~Variant() {
		Destroy();
	}

	void Destroy() {
		if(bObjectValid) GetTypeHolder()->destruct(object);
	}

	template<typename T>
	T* ConstructAs()
	{
		static_assert(sizeof(T) <= Nbytes, "The preallocated buffer isn't large enough");

		if(bObjectValid != 0) GetTypeHolder()->destruct(object);
		new (typeHolder) TypeHolder<T>();
		GetTypeHolder()->constr(object);

		bObjectValid = true;

		return (T*) object;
	}

	template<typename T>
	T& As() { return *((T*) object); }

	std::string NodeGenerateCode(const LangSetting& lang) { 
		return GetTypeHolder()->CallGenerateCode(object, lang); 
	}

	void NodeDelcare(Ast* ast) {
		GetTypeHolder()->CallNodeDeclare(object, ast);
	}

	TypeDesc NodeDeduceType() {
		return GetTypeHolder()->CallDeduceType(object);
	}

private :

	struct Base
	{
		virtual void constr(void*) const = 0;
		virtual void destruct(void*) const = 0;

		virtual std::string CallGenerateCode(void* p, const LangSetting& lang) const = 0;
		virtual void CallNodeDeclare(void* p, Ast* ast) const = 0;
		virtual TypeDesc CallDeduceType(void* p) const = 0;
	};

	struct Dummy {
	
	};

	template<typename T>
	struct TypeHolder : Base
	{
		void constr(void* p) const override { new (p) T; }
		void destruct(void* p) const override { ((T*)(p))->~T(); }

		std::string CallGenerateCode(void* p, const LangSetting& lang) const override {return ::NodeGenerateCode(lang, *((T*)(p))); }
		void CallNodeDeclare(void* p, Ast* ast) const override { ::NodeDeclare(ast,  *((T*)(p))); }
		TypeDesc CallDeduceType(void* p) const override { return ::NodeDeduceType(*((T*)(p))); }
	};

	char object[Nbytes];
	char typeHolder[sizeof(TypeHolder<Dummy>)];
	unsigned char bObjectValid;

	Base* GetTypeHolder() { return (Base*)typeHolder; }
};
