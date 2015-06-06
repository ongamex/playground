#pragma once

#include <string>

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

	std::string GenerateGLSL() { return GetTypeHolder()->CallGenerateGLSL(object); }

private :

	struct Base
	{
		virtual void constr(void*) const = 0;
		virtual void destruct(void*) const = 0;

		virtual std::string CallGenerateGLSL(void*) const = 0;
	};

	struct Dummy {std::string GenerateGLSL() { return std::string(); } };

	template<typename T>
	struct TypeHolder : Base
	{
		void constr(void* p) const override { new (p) T; }
		void destruct(void* p) const override { ((T*)(p))->~T(); }

		std::string CallGenerateGLSL(void* p) const override { return ((T*)(p))->GenerateGLSL(); }
	};


	char object[Nbytes];
	char typeHolder[sizeof(TypeHolder<Dummy>)];
	unsigned char bObjectValid;

	Base* GetTypeHolder() { return (Base*)typeHolder; }
};