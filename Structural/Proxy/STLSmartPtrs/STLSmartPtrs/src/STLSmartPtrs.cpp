#include <iostream>
using namespace std;

struct BankAccount
{
	virtual ~BankAccount() = default;
	virtual void deposit(int amount) = 0;
	virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount
{
	explicit CurrentAccount(const int balance) :
		balance{ balance }
	{}

	void deposit(int amount) override
	{
		balance += amount;
	}
	void withdraw(int amount) override
	{
		if (balance >= amount) balance -= amount;
	}

	friend ostream& operator<<(ostream& os, const CurrentAccount& obj)
	{
		return os << "Balance: " << obj.balance;
	}

private:
	int balance = 0;
};

void smart_pointers()
{
	CurrentAccount* a = new CurrentAccount{ 1000 };
	a->deposit(1000);
	cout << "a: " << *a << endl;
	delete a;

	shared_ptr<CurrentAccount> b = make_shared<CurrentAccount>(2000);
	b->deposit(2000);
	cout << "b: " << *b << endl;

	CurrentAccount* underlying = b.get();
}

int main()
{
	smart_pointers();

	return 0;
}