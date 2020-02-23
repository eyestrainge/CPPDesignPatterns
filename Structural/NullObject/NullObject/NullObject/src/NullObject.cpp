#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Logger
{
	virtual ~Logger() = default;
	virtual void info(const string& s) = 0;
	virtual void warn(const string& s) = 0;
};

struct ConsoleLogger : Logger
{
	void info(const string& s) override
	{
		cout << "INFO: " << s << endl;
	}

	void warn(const string& s) override
	{
		cout << "WARN: " << s << endl;
	}
};

struct NullLogger : Logger
{
	void info(const string& s) override {}
	void warn(const string& s) override {}
};

struct BankAccount
{
	std::shared_ptr<Logger> log;
	string name;
	int balance = 0;

	BankAccount(
		const std::shared_ptr<Logger>& logger,
		const string& name,
		int balance
	) :
		log{ logger },
		name{ name },
		balance{ balance }
	{}

	void deposit(int amount)
	{
		balance += amount;
		log->info(
			"Deposited $" + lexical_cast<string>(amount)
			+ " to " + name + ", balance is now $"
			+ lexical_cast<string>(balance)
		);
	}

	void withdraw(int amount)
	{
		if (balance >= amount)
		{
			balance -= amount;
			log->info(
				"Withdrew $" + lexical_cast<string>(amount)
				+ " from " + name + ", $"
				+ lexical_cast<string>(balance) + " left"
			);
		}
		else
		{
			log->warn(
				"Tried to withdraw $" + lexical_cast<string>(amount)
				+ " from " + name + " but couldn't due to low balance"
			);
		}
	}
};

int main()
{
	// Assumed working version
	//auto logger = make_shared<ConsoleLogger>();
	// Crash
	//std::shared_ptr<Logger> logger;
	// NullObject
	auto logger = make_shared<NullLogger>();
	BankAccount account{ logger, "primary account", 1000 };

	// If there are return values which are somehow context
	// sensitive, to be dependent on them rises additional
	// complications...

	account.deposit(1000);
	account.withdraw(1500);
	account.withdraw(1000);

	return 0;
}