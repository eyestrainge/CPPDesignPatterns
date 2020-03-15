#include <string>
#include <vector>
#include <mutex>
#include <iostream>
#include <boost/any.hpp>
using namespace std;
using namespace boost;

struct Person;

static mutex mtx;

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
		lock_guard<mutex> guard{ mtx };
		if (find(begin(listeners), end(listeners), pl) == end(listeners))
			listeners.push_back(pl);
	}

	void unsubscribe(PersonListener* pl)
	{
		lock_guard<mutex> guard{ mtx };
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (*it == pl)
				*it = nullptr;
		}
	}

	void notify(const string& propery_name, const any new_value)
	{
		lock_guard<mutex> guard{ mtx };
		for (const auto listener : listeners)
			if (listener)
				listener->PersonChanged(*this, propery_name, new_value);

		listeners.erase(
			remove(listeners.begin(), listeners.end(), nullptr),
			listeners.end()
		);
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

struct BadListener : PersonListener
{
	void PersonChanged(
		Person& p,
		const string& property_name,
		const any new_value
	) override
	{
		p.unsubscribe(this);
	}
};

int main()
{
	Person p{ 16 };
	ConsoleListener cl;
	//BadListener cl; // Reentrancy issue
	p.subscribe(&cl);
	p.subscribe(&cl);
	p.SetAge(17);
	p.SetAge(18);
	p.unsubscribe(&cl);
	p.SetAge(19);

	return 0;
}