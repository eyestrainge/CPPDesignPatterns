#include "di.hpp"
#include <iostream>
#include <memory>

struct ILogger
{
	virtual ~ILogger() {}

	virtual void Log(const std::string& s) = 0;
};

struct ConsoleLogger : ILogger
{
	void Log(const std::string& s) override
	{
		std::cout << "LOG: " << s.c_str() << std::endl;
	}
};

struct Engine
{
	float CC = 4.8;
	int HP = 362;

	explicit Engine() {}

	friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
	{
		return os
			<< "  CC: " << obj.CC
			<< "  HP: " << obj.HP;
	}
};

// Car depends on engine
struct Car
{
	std::shared_ptr<Engine> engine;
	std::shared_ptr<ILogger> logger;

	explicit Car(
		const std::shared_ptr<Engine>& engine,
		const std::shared_ptr<ILogger>& logger
	) :
		engine{ engine },
		logger{ logger }
	{
		logger->Log("Created a car.");
	}

	friend std::ostream& operator<<(std::ostream& os, const Car& obj)
	{
		return os << "Car with engine:" << *obj.engine;
	}
};

int main()
{
	/*auto e = std::make_shared<Engine>();
	auto c = std::make_shared<Car>(e);*/

	auto injector = boost::di::make_injector(
		boost::di::bind<ILogger>().to<ConsoleLogger>()
	);
	auto c = injector.create<std::shared_ptr<Car>>();

	std::cout << *c << std::endl;

	return 0;
}