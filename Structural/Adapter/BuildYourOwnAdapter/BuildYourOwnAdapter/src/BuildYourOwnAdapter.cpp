#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

class String
{
	std::string s;

public:
	String(const std::string& s) :
		s{ s }
	{}

	String to_lower() const
	{
		std::string S{ s };
		boost::to_lower(S);

		return { S };
	}

	std::vector<std::string> split(const std::string& delimiter = " ") const
	{
		std::vector<std::string> result;
		boost::split(result, s, boost::is_any_of(delimiter), boost::token_compress_on);

		return result;
	}
};

int main()
{
	String s{ "Hello World!" };

	auto tokens = s.to_lower().split();

	for (const auto& t : tokens)
		std::cout << t << std::endl;

	return 0;
}