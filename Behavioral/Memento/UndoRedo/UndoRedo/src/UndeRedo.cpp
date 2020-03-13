#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class Memento
{
	int balance;

public:
	Memento(const int balance) :
		balance{ balance }
	{}

	friend class BankAccount;
	friend class BankAccount2;
};

class BankAccount
{
	int balance = 0;

public:
	explicit BankAccount(const int balance) :
		balance{ balance }
	{}

	Memento deposit(int amount)
	{
		balance += amount;
		return{ balance };
	}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	friend ostream& operator<<(ostream& os, const BankAccount& obj)
	{
		return os << "Balance: " << obj.balance;
	}
};

class BankAccount2
{
	int balance = 0;
	vector<shared_ptr<Memento>> changes;
	int current;

public:
	explicit BankAccount2(const int balance) :
		balance{ balance }
	{
		changes.emplace_back(make_shared<Memento>(balance));
		current = 0;
	}

	shared_ptr<Memento> deposit(int amount)
	{
		balance += amount;
		auto m = make_shared<Memento>(balance);
		changes.push_back(m);
		++current;
		return m;
	}

	void restore(const shared_ptr<Memento>& m)
	{
		if (m)
		{
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
		}
	}

	shared_ptr<Memento> undo()
	{
		if (current > 0)
		{
			--current;
			auto m = changes[current];
			balance = m->balance;
		}
		return{};
	}

	shared_ptr<Memento> redo()
	{
		if (current + 1 < changes.size())
		{
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		return{};
	}

	friend ostream& operator<<(ostream& os, const BankAccount2& obj)
	{
		return os << "Balance: " << obj.balance;
	}
};

int main()
{
	BankAccount2 ba{ 100 };
	ba.deposit(50); // 150
	ba.deposit(25); // 175
	cout << ba << "\n";

	ba.undo();
	cout << "Undo 1: " << ba << "\n";
	ba.undo();
	cout << "Undo 2: " << ba << "\n";
	ba.redo();
	cout << "Redo 1: " << ba << "\n";

	return 0;
}