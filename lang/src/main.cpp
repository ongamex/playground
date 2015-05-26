#include <iostream>

#include "ast.h"
#include "lang.tab.h"

Ast g_ast;

int kk_parse_cstring(const char* str);

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
	T* SetVariant()
	{
		static_assert(sizeof(T) <= Nbytes, "The preallocated buffer isn't large enough");

		if(bObjectValid != 0) GetTypeHolder()->destruct(object);
		new (typeHolder) TypeHolder<T>();
		GetTypeHolder()->constr(object);

		bObjectValid = true;

		return (T*) object;
	}

private :

	struct Base
	{
		virtual void constr(void*) const = 0;
		virtual void destruct(void*) const = 0;
	};

	struct Dummy {};

	template<typename T>
	struct TypeHolder : Base
	{
		void constr(void* p) const override { new (p) T; }
		void destruct(void* p) const override { ((T*)(p))->~T(); }
	};


	char object[Nbytes];
	char typeHolder[sizeof(TypeHolder<Dummy>)];
	unsigned char bObjectValid;

	Base* GetTypeHolder() { return (Base*)typeHolder; }
};

struct Foo { int x = 1131; };

int main()
{
	int sz = sizeof(Variant<sizeof(Foo)>); // 5 + 4
	Variant<sizeof(Foo)> var;
	auto f = var.SetVariant<Foo>();
	

	yyparse();

	//kk_parse_cstring("if(1) { 5; }\n\0\0");

	g_ast.nodes.back()->printMe(00);

	std::cin.get();

	return 0;
}