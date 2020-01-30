#include "Singleton.hpp"
#include <gtest/gtest.h>

TEST(DatabaseTests, IsSingletonTest)
{
	auto& sdb = SingletonDatabase::get();
	auto& sdb2 = SingletonDatabase::get();
	ASSERT_EQ(1, sdb.instance_count);
	ASSERT_EQ(1, sdb2.instance_count);
}

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
	SingletonRecordFinder srf;
	std::vector<std::string> names{ "Seoul", "Mexico City" };
	int tp = srf.total_population(names);
	EXPECT_EQ(17500000 + 17400000, tp);
}

TEST(RecordFinderTests, DependentTotalPopulationTest)
{
	DummyDatabase ddb;
	ConfigurableRecordFinder crf{ ddb };
	EXPECT_EQ(4, crf.total_population(std::vector<std::string>{"alpha", "gamma"}));
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}