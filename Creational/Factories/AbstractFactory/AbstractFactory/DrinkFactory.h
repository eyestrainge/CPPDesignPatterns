#pragma once

#include "HotDrinkFactory.h"
#include "TeaFactory.h"
#include "CoffeeFactory.h"



class DrinkFactory
{
	std::map<std::string, std::unique_ptr<HotDrinkFactory>> HotDrinks;

public:
	DrinkFactory()
	{
		HotDrinks["tea"] = std::make_unique<TeaFactory>();
		HotDrinks["coffee"] = std::make_unique<CoffeeFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name)
	{
		auto drink = HotDrinks[name]->make();
		drink->prepare(200);

		return drink;
	}
};



class DrinkWithVolumeFactory
{
	std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = []
		{
			auto tea = std::make_unique<Tea>();
			tea->prepare(250);
			return tea;
		};
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name)
	{
		return factories[name]();
	}
};
