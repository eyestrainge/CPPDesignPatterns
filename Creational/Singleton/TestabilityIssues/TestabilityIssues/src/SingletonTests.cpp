#include "Singleton.hpp"
#include <gtest/gtest.h>

TEST(DatabaseTests, IsSingletonTest)
{
	auto& db = SingletonDatabase::get();
	auto& db2 = SingletonDatabase::get();
	ASSERT_EQ(1, db.instance_count);
	ASSERT_EQ(1, db2.instance_count);
}

TEST(RecordFinderTest, SingletonTotalPopulationTest)
{
	SingletonRecordFinder rf;
	std::vector<std::string> names{ "Seoul", "Mexico City" };
	int tp = rf.total_population(names);
	EXPECT_EQ(17500000 + 17400000, tp);
}

int main(int ac, char* av[])
{
	SingletonRecordFinder rf2;
	std::vector<std::string> names{ "Seoul", "Mexico City" };
	int tp2 = rf2.total_population(names);

	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}