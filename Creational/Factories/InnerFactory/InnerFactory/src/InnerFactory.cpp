#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

class Point
{
private:
	float x, y;

	Point(const float x, const float y):
		x{ x },
		y{ y }
	{}

	class PointFactory
	{
	public:
		static Point NewCartesian(const float x, const float y)
		{
			return{ x, y };
		}

		static Point NewPolar(const float r, const float theta)
		{
			return{ r * cos(theta), r * sin(theta) };
		}
	};

public:
	friend std::ostream& operator<<(std::ostream& os, const Point& obj)
	{
		return os
			<< "X = " << obj.x << "  "
			<< "Y = " << obj.y;
	}

	static PointFactory Factory;
};

int main()
{
	auto C = Point::Factory.NewCartesian(1, 2);
	auto P = Point::Factory.NewPolar(5, M_PI_4);

	std::cout
		<< C << "\n"
		<< P << std::endl;

	return 0;
}