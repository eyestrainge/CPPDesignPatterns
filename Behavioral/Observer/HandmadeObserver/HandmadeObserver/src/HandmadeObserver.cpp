#include <string>
#include <vector>
#include <iostream>
#include <boost/any.hpp>
using namespace std;
using namespace boost;

struct Person;

struct PersonListener
{
	virtual ~PersonListener() = default;

	virtual void PersonChanged(
		Person& p,
		const string& property_name,
		const any new_value
	) = 0;
};

struct Person
{
	explicit Person(const int age) :
		age{ age }
	{}

	virtual int GetAge() const { return age; }
	bool GetCanVote() const { return age >= 18; }
	virtual void SetAge(const int age)
	{
		if (this->age == age) return;

		auto old_c_v = GetCanVote();

		this->age = age;
		notify("age", this->age);

		auto new_c_v = GetCanVote();
		if (old_c_v != new_c_v)
			notify("can_vote", new_c_v);
	}

	void subscribe(PersonListener* pl)
	{
		listeners.push_back(pl);
	}

	void notify(const string& propery_name, const any new_value)
	{
		for (const auto listener : listeners)
			listener->PersonChanged(*this, propery_name, new_value);
	}

private:
	int age;
	vector<PersonListener*> listeners;
};

struct ConsoleListener : PersonListener
{
	void PersonChanged(
		Person& p,
		const string& property_name,
		const any new_value
	) override
	{
		cout << "Person's " << property_name << " has been changed to ";
		if (property_name == "age")
			cout << any_cast<int>(new_value);
		else if (property_name == "can_vote")
			cout << any_cast<bool>(new_value);
		cout << "\n";
	}
};

int main()
{
	Person p{ 16 };
	ConsoleListener cl;
	p.subscribe(&cl);
	p.SetAge(17);
	p.SetAge(18);

	return 0;
}