// 2 + (3+4)

#include <vector>
#include <iostream>
#include <memory>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

struct Expression
{
	virtual double eval() = 0;
	virtual void collect(std::vector<double>& v) = 0;
};

struct Literal : Expression
{
	double value;

	explicit Literal(const double value) :
		value{ value }
	{}

	double eval() override
	{
		return value;
	}

	void collect(std::vector<double>& v) override
	{
		v.push_back(value);
	}
};

struct AdditionExpression : Expression
{
	std::shared_ptr<Expression> left, right;

	AdditionExpression(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right) :
		left{ left },
		right{ right }
	{}

	double eval() override
	{
		return left->eval() + right->eval();
	}

	void collect(std::vector<double>& v) override
	{
		left->collect(v);
		right->collect(v);
	}
};

int main()
{
	AdditionExpression sum{
		std::make_shared<Literal>(2),
		std::make_shared<AdditionExpression>(
			std::make_shared<Literal>(3),
			std::make_shared<Literal>(4)
		)
	};

	std::cout << "2 + (3+4) = " << sum.eval() << std::endl;

	std::vector<double> v;
	sum.collect(v);

	for (auto x : v)
		std::cout << x << "\t";
	std::cout << std::endl;

	std::vector<double> values{ 1,2,3,4 };
	double s = 0;
	for (auto x : values) s += x;
	std::cout << "Average of values = " << s / values.size() << std::endl;

	boost::accumulators::accumulator_set<
		double,
		boost::accumulators::stats<boost::accumulators::tag::mean>
	> acc;
	for (auto x : values) acc(x);
	std::cout << "Average of values = " << boost::accumulators::mean(acc) << std::endl;

	return 0;
}