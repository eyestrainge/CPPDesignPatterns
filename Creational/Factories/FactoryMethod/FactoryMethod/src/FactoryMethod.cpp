#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>



//enum class PointType
//{
//	cartesian,
//	polar
//};



class Point
{
private:
	Point(const float x, const float y) :
		x{ x },
		y{ y }
	{}

public:
	float x, y;



	/*Point(const float a, const float b, PointType type = PointType::cartesian)
	{
		if (type == PointType::cartesian)
		{
			x = a;
			y = b;
		}
		else
		{
			x = a * cos(b);
			y = a * sin(b);
		}
	}*/

	/*static Point NewCartesian(const float x, const float y)
	{
		return{ x, y };
	}

	static Point NewPolar(const float r, const float theta)
	{
		return{ r * cos(theta), r * sin(theta) };
	}*/



	friend std::ostream& operator<<(std::ostream& os, const Point& obj)
	{
		return os
			<< "X = " << obj.x << " "
			<< "Y = " << obj.y;
	}

	friend class PointFactory;
};

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

int main()
{
	/*auto c = Point::NewCartesian(1, 2);
	auto p = Point::NewPolar(5, M_PI_4);*/



	auto c = PointFactory::NewCartesian(1, 2);
	auto p = PointFactory::NewPolar(5, M_PI_4);

	std::cout << c << std::endl;
	std::cout << p << std::endl;

	return 0;
}