#include <string>
#include <iostream>

struct Address { std::string* house_name = nullptr; };
struct Person { Address* address = nullptr; };

template <typename T> struct Maybe;

template <typename T> Maybe<T> maybe(T* context)
{
	return Maybe<T>(context);
}

template <typename T> struct Maybe
{
	T* context;

	Maybe(T* context) : context{ context } {}

	template <typename F> auto With(F evaluator)
	{
		return context != nullptr ? maybe(evaluator(context)) : nullptr;
	}

	template <typename F> auto Do(F action)
	{
		if (context != nullptr) action(context);
		return *this;
	}
};

void print_house_name(Person* p)
{
	/*if (p && p->address && p->address->house_name)
		std::cout << *p->address->house_name << std::endl;*/

	maybe(p)
		.With([](auto x) { return x->address; })
		.With([](auto x) { return x->house_name; })
		.Do([](auto x) { std::cout << *x << std::endl; });
}

int main()
{
	Person p;
	p.address = new Address;
	p.address->house_name = new std::string("Lothric Castle");

	print_house_name(&p);

	delete p.address->house_name;
	delete p.address;

	return 0;
}