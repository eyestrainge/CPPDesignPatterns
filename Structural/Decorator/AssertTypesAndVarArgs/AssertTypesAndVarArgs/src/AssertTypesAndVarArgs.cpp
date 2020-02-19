#include <string>
#include <sstream>
#include <iostream>

struct Shape
{
	virtual std::string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	explicit Circle(const float radius) :
		radius{ radius }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}
};

struct Square : Shape
{
	float side;

	explicit Square(const float side) :
		side{ side }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}
};

struct ColoredShape : Shape
{
	Shape& shape;
	std::string color;

	ColoredShape(Shape& shape, const std::string& color) :
		shape{ shape },
		color{ color }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << shape.str() << " has the color " << color;
		return oss.str();
	}
};

struct TransparentShape : Shape
{
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& shape, const uint8_t& transparency) :
		shape{ shape },
		transparency{ transparency }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss
			<< shape.str()
			<< " has "
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";
		return oss.str();
	}
};

template <typename T>
struct ColoredShape2 : T
{
	static_assert(
		std::is_base_of<Shape, T>::value,
		"Template argument must be a Shape"
	);

	std::string color;

	ColoredShape2(const std::string& color) :
		color{ color }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}
};

template <typename T>
struct TransparentShape2 : T
{
	static_assert(
		std::is_base_of<Shape, T>::value,
		"Template argument must be a Shape"
	);

	uint8_t transparency;

	template <typename ...Args>
	TransparentShape2(const uint8_t& transparency, Args ...args) :
		T(std::forward<Args>(args)...),
		transparency{ transparency }
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss
			<< T::str()
			<< " has "
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";
		return oss.str();
	}
};

int main()
{
	// Template argument must be a Shape
	/*struct NotAShape
	{
		virtual std::string str() const { return std::string{}; }
	};
	ColoredShape2<NotAShape> legal;*/

	TransparentShape2<Square> hidden_square{ 0, 15 };
	std::cout << hidden_square.str() << std::endl;

	return 0;
}