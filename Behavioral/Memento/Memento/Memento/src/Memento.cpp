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

int main()
{
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50); // 150
	auto m2 = ba.deposit(25); // 175
	cout << ba << endl;

	ba.restore(m1);
	cout << ba << endl;

	ba.restore(m2);
	cout << ba << endl;

	return 0;
}