#pragma once
#include <string>
#include <vector>
using namespace std;

struct Person;

struct ChatRoom
{
	vector<Person> people;

	class PersonReference
	{
		vector<Person>& people;
		unsigned int index;

	public:
		PersonReference(vector<Person>& people, const unsigned index) :
			people{ people },
			index{ index }
		{}

		Person* operator->() const;
	};

	void broadcast(const string& origin, const string& message);

	PersonReference join(Person&& p);

	void message(const string& origin, const string& who, const string& message);
};