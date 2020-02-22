#include <string>
#include <iostream>
#include <boost/bimap.hpp>

using namespace std;
using namespace boost;

typedef uint32_t key;

struct User
{
	//string first_name, last_name;

	User(const string& first_name, const string& last_name) :
		//first_name{ first_name },
		//last_name{ last_name }
		first_name{ add(first_name) },
		last_name{ add(last_name) }
	{}

	const string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	const string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

	friend ostream& operator<<(ostream& os, const User& obj)
	{
		return os
			<< "first name: " << obj.first_name << " " << obj.get_first_name() << "\t"
			<< "last name: " << obj.last_name << " " << obj.get_last_name() << "\n";
	}

protected:
	key first_name, last_name;

	static bimap<key, string> names;
	static int seed;

	static key add(const string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert(bimap<key, string>::value_type(seed, s));
			return id;
		}
		return it->second;
	}
};

bimap<key, string> User::names{};
int User::seed = 0;

int main(int ac, char* av)
{
	User john_doe{ "John", "Doe" };
	User jane_doe{ "Jane", "Doe" };
	User jane_lee{ "Jane", "Lee" };

	cout << "John\t" << john_doe;
	cout << "JDoe\t" << jane_doe;
	cout << "JLee\t" << jane_lee;

	return 0;
}