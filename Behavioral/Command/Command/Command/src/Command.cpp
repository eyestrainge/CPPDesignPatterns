#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct BankAccount
{
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount)
	{
		balance += amount;
		cout << "deposited " << amount << ", balance now " << balance << "\n";
	}

	void withdraw(int amount)
	{
		if (balance - amount >= overdraft_limit)
		{
			balance -= amount;
			cout << "withdrew " << amount << ", balance now " << balance << "\n";
		}
	}
};

struct Command
{
	BankAccount& account; // Could be serialized using UUID to track
	enum Action { deposit, withdraw } action;
	int amount;

	Command(BankAccount& account, const Action action, const int amount) :
		account{ account },
		action{ action },
		amount{ amount }
	{}

	void call() const
	{
		switch (action)
		{
		case deposit:
			account.deposit(amount);
			break;
		case withdraw:
			account.withdraw(amount);
			break;
		default:
			break;
		}
	}
};

int main()
{
	BankAccount ba;
	/*ba.deposit(100);
	ba.withdraw(200);*/
	vector<Command> commands
	{
		Command{ ba, Command::deposit, 100 },
		Command{ ba, Command::withdraw, 200 }
	};

	for (auto& cmd : commands)
		cmd.call();

	return 0;
}