#include <vector>
#include <map>
#include <iostream>
using namespace std;

enum class State
{
	OffHook, Connecting, Connected, OnHold
};

inline ostream& operator<<(ostream& os, const State& s)
{
	switch (s)
	{
	case State::OffHook:
		os << "Off the hook"; break;
	case State::Connecting:
		os << "Connecting"; break;
	case State::Connected:
		os << "Connected"; break;
	case State::OnHold:
		os << "On hold"; break;
	default: break;
	}
	return os;
}

enum class Trigger
{
	CallDialed, HungUp, CallConnected, PlacedOnHold, TakenOffHold, LeftMessage
};

inline ostream& operator<<(ostream& os, const Trigger& t)
{
	switch (t)
	{
	case Trigger::CallDialed:
		os << "Call dialed"; break;
	case Trigger::HungUp:
		os << "Hung up"; break;
	case Trigger::CallConnected:
		os << "Call connected"; break;
	case Trigger::PlacedOnHold:
		os << "Placed on hold"; break;
	case Trigger::TakenOffHold:
		os << "Taken off hold"; break;
	case Trigger::LeftMessage:
		os << "Left message"; break;
	default: break;
	}
	return os;
}

int main()
{
	map<State, vector<pair<Trigger, State>>> rules;

	rules[State::OffHook] = {
		{Trigger::CallDialed, State::Connecting}
	};
	rules[State::Connecting] = {
		{Trigger::HungUp, State::OffHook},
		{Trigger::CallConnected, State::Connected}
	};
	rules[State::Connected] = {
		{Trigger::LeftMessage, State::OffHook},
		{Trigger::HungUp, State::OffHook},
		{Trigger::PlacedOnHold, State::OnHold}
	};
	rules[State::OnHold] = {
		{Trigger::TakenOffHold, State::Connected},
		{Trigger::HungUp, State::OffHook}
	};

	State currentState{ State::OffHook };

	while (true)
	{
		cout << "The phone is currently " << currentState << endl;
	select_trigger:
		cout << "Select a trigger:" << "\n";

		int i = 0;
		for (auto item : rules[currentState])
			cout << i++ << ". " << item.first << "\n";

		int input;
		cin >> input;
		if (input < 0 || (input + 1) > rules[currentState].size())
		{
			cout << "Incorrect option. Please try again." << "\n";
			goto select_trigger;
		}

		currentState = rules[currentState][input].second;
	}

	cout << "We are done using the phone" << "\n";

	return 0;
}