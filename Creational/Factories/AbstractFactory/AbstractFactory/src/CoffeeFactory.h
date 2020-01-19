#pragma once

#include "HotDrinkFactory.h"

struct CoffeeFactory : HotDrinkFactory
{
	std::unique_ptr<HotDrink> make()
	{
		return std::make_unique<Coffee>();
	}
};