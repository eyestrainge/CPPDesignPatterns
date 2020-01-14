#include <string>
#include <vector>
#include <iostream>



enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };



struct Product
{
	std::string name;
	Color color;
	Size size;
};



//struct ProductFilter
//{
//	static std::vector<Product*> by_color(std::vector<Product*> items, Color color)
//	{
//		std::vector<Product*> results;
//		for (auto& item : items)
//			if (item->color == color)
//				results.push_back(item);
//		return results;
//	}
//};



template <typename T> struct ISpecification
{
	virtual bool is_satisfied(T* item) = 0;
};



template <typename T> struct IFilter
{
	virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};



struct ColorSpecification : ISpecification<Product>
{
	Color color;

	ColorSpecification(const Color color):
		color(color) {}

	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}
};



struct SizeSpecification : ISpecification<Product>
{
	Size size;

	SizeSpecification(const Size size):
		size(size) {}

	bool is_satisfied(Product* item) override
	{
		return item->size == size;
	}
};



template <typename T> struct AndSpecification : ISpecification<T>
{
	ISpecification<T>& first;
	ISpecification<T>& second;

	AndSpecification(ISpecification<T>& first, ISpecification<T>& second):
		first(first),
		second(second)
	{}

	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};



struct BetterFilter : IFilter<Product>
{
	std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product>& spec) override
	{
		std::vector<Product*> results;

		for (auto& item : items)
			if (spec.is_satisfied(item))
				results.push_back(item);

		return results;
	}
};



int main()
{
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };

	std::vector<Product*> products{ &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::Green);
	SizeSpecification large(Size::Large);
	AndSpecification<Product> green_large{ green, large };

	auto green_things = bf.filter(products, green);
	auto green_large_things = bf.filter(products, green_large);

	for (auto& product : green_things)
		std::cout << product->name << " is green" << std::endl;
	for (auto& product : green_large_things)
		std::cout << product->name << " is green and large" << std::endl;

	return 0;
}
