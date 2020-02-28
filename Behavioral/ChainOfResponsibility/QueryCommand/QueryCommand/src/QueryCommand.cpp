#include <string>
#include <iostream>
#include <boost/signals2.hpp>
using namespace std;
using namespace boost::signals2;

struct Query
{
	string creature_name;
	enum Argument { attack, defense } argument;
	int result;

	Query(const string& creature_name, const Argument argument, const int result) :
		creature_name{ creature_name },
		argument{ argument },
		result{ result }
	{}
};

struct Game
{
	signal<void(Query&)> queries;
};

class Creature
{
	Game& game;
	int attack, defense;

public:
	string name;

	Creature(Game& game, const int attack, const int defense, const string& name) :
		game{ game },
		attack{ attack },
		defense{ defense },
		name{ name }
	{}

	int GetAttack() const
	{
		Query q{ name, Query::Argument::attack, attack };
		game.queries(q);
		return q.result;
	}

	friend ostream& operator<<(ostream& os, const Creature& obj)
	{
		return os
			<< "Name: " << obj.name
			<< "\n--Attack:\t" << obj.GetAttack()
			<< "\n--Defense:\t" << obj.defense << "\n";
	}
};

class CreatureModifier
{
	Game& game;
	Creature& creature;

public:
	CreatureModifier(Game& game, Creature& creature) :
		game{ game },
		creature{ creature }
	{}
	virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : CreatureModifier
{
	connection conn;

public:
	DoubleAttackModifier(Game& game, Creature& creature) :
		CreatureModifier{ game, creature }
	{
		conn = game.queries.connect([&](Query& q)
		{
			if (q.creature_name == creature.name
				&&
				q.argument == Query::Argument::attack)
			{
				q.result *= 2;
			}
		});
	}
	virtual ~DoubleAttackModifier()
	{
		conn.disconnect();
	}
};

int main(int argc, char** argv)
{
	Game game;
	Creature goblin{ game, 2, 2, "Strong Goblin" };
	cout << goblin << endl;

	{
		DoubleAttackModifier am{ game, goblin };
		cout << goblin << endl;
	}

	cout << goblin << endl;

	return 0;
}