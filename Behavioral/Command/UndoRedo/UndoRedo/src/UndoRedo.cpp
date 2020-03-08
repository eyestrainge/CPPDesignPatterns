#include <string>
#include <vector>
#include <algorithm>
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

	void undo() const
	{
		switch (action)
		{
		case withdraw:
			account.deposit(amount);
			break;
		case deposit:
			account.withdraw(amount);
			break;
		default:
			break;
		}
	}

	void redo() const
	{
		call();
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

	cout << ba.balance << endl;

	for (auto& cmd : commands)
		cmd.call();

	cout << ba.balance << endl;

	for (auto& cmd : commands)
		cmd.call();

	cout << ba.balance << endl;

	for_each(
		commands.rbegin(),
		commands.rend(),
		[](const Command& cmd) { cmd.undo(); }
	);

	cout << ba.balance << endl;

	for_each(
		commands.rbegin(),
		commands.rend(),
		[](const Command& cmd) { cmd.undo(); }
	);

	cout << ba.balance << endl;

	for_each(
		commands.begin(),
		commands.end(),
		[](const Command& cmd) { cmd.redo(); }
	);

	cout << ba.balance << endl;

	for_each(
		commands.begin(),
		commands.end(),
		[](const Command& cmd) { cmd.redo(); }
	);

	cout << ba.balance << endl;

	return 0;
}