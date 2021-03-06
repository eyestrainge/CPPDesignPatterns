#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
	}

	static SingletonDatabase* instance;

public:
	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	static SingletonDatabase* get_instance()
	{
		// Not thread safe
		if (!instance)
			instance = new SingletonDatabase;
		return instance; // atexit could work but cryptic
	}
};