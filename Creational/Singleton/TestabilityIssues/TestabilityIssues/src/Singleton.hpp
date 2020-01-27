#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <boost/lexical_cast.hpp>

class SingletonDatabase
{
	std::map<std::string, int> capitals;

	SingletonDatabase()
	{
		std::cout << "Initializing database" << std::endl;

		std::ifstream ifs("capitals.txt");
		std::string s, s2;

		while (std::getline(ifs, s))
		{
			std::getline(ifs, s2);
			int pop = boost::lexical_cast<int>(s2);
			capitals[s] = pop;
		}

		instance_count++;
	}

public:
	static int instance_count;

	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	static SingletonDatabase& get()
	{
		static SingletonDatabase db;
		return db;
	}

	int get_population(const std::string& name)
	{
		return capitals[name];
	}
};

int SingletonDatabase::instance_count = 0;

struct SingletonRecordFinder
{
	int total_population(std::vector<std::string> names)
	{
		int result = 0;
		for (auto& name : names)
			result += SingletonDatabase::get().get_population(name);
		return result;
	}
};