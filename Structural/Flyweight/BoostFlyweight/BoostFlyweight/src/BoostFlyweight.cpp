#include <string>
#include <iostream>
#include <boost/flyweight.hpp>

using namespace std;
using namespace boost;

struct User
{
	flyweight<string> first_name, last_name;

	User(const string& first_name, const string& last_name) :
		first_name{ first_name },
		last_name{ last_name }
	{}

	friend ostream& operator<<(ostream& os, const User& obj)
	{
		return os
			<< "first name: " << obj.first_name << "\t"
			<< "last name: " << obj.last_name;
	}
};

int main()
{
	User john_doe{ "John", "Doe" };
	User jane_doe{ "Jane", "Doe" };

	cout << john_doe << "\n" << jane_doe << endl;

	cout
		<< boolalpha
		<< (&john_doe.last_name.get() == &jane_doe.last_name.get())
		<< endl;

	return 0;
}