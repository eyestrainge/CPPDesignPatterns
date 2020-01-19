#include <iostream>

class Rectangle
{
protected:
	int width, height;

public:
	Rectangle(const int width, const int height) :
		width{ width },
		height{ height }
	{}

	virtual int GetWidth() const
	{
		return width;
	}
	virtual void SetWidth(const int width)
	{
		this->width = width;
	}
	virtual int GetHeight() const
	{
		return height;
	}
	virtual void SetHeight(const int height)
	{
		this->height = height;
	}

	int area() const { return width * height; }
};



//class Square : public Rectangle
//{
//public:
//	Square(int size) : Rectangle{ size, size } {}
//
//	/*void SetWidth(const int width) override
//	{
//		this->width = height = width;
//	}
//	void SetHeight(const int height) override
//	{
//		this->height = width = height;
//	}*/
//
//	//void SetSize
//};



struct RectangleFactory
{
	static Rectangle CreateRectangle(int w, int h);
	static Rectangle CreateSquare(int s);
};

void process(Rectangle& r)
{
	int w = r.GetHeight();
	r.SetHeight(10);

	std::cout
		<< "Expected area = " << (w * r.GetHeight())
		<< ", got: " << r.area() << std::endl;
}

int main()
{
	Rectangle r{ 5,5 };
	process(r);

	/*Square s{ 5 };
	process(s);*/

	return 0;
}