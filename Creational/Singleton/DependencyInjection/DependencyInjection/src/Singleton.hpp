#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

class Database
{
public:
	virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
	std::map<std::string, int> capitals;

	SingletonDatabase()
	{
		std::cout << "Initializing database" << std::endl;

		std::ifstream ifs("src/capitals.txt");
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

	int get_population(const std::string& name) override
	{
		return capitals[name];
	}
};

int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database
{
	std::map<std::string, int> capitals;

public:
	DummyDatabase()
	{
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		capitals["gamma"] = 3;
	}

	int get_population(const std::string& name) override
	{
		return capitals[name];
	}
};

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

struct ConfigurableRecordFinder
{
	Database& db;

	explicit ConfigurableRecordFinder(Database& db) :
		db{ db }
	{}

	int total_population(std::vector<std::string> names)
	{
		int result = 0;
		for (auto& name : names)
			result += db.get_population(name);
		return result;
	}
};