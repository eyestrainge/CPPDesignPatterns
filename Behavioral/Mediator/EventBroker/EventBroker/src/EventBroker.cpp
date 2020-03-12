#include <string>
#include <iostream>
#include <boost/signals2.hpp>
using namespace std;
using namespace boost::signals2;

struct Player;

struct Event
{
	virtual ~Event() = default;
	virtual void print() const = 0;
};

struct Game // Event Bus/Broker
{
	signal<void(Event*)> events; // Observer pattern
};

struct PlayerScored : Event
{
	string player_name;
	int goals_scored;

	PlayerScored(const string& player_name, const int goals_scored) :
		player_name{ player_name },
		goals_scored{ goals_scored }
	{}

	void print() const override;
};

void PlayerScored::print() const
{
	cout << player_name << " has scored (their " << goals_scored << " goal)" << "\n";
}

struct Player
{
	Game& game;
	string name;
	int goals_scored = 0;

	Player(Game& game, const string& name) :
		game{ game },
		name{ name }
	{}

	void score()
	{
		goals_scored++;
		PlayerScored ps{ name, goals_scored };
		game.events(&ps);
	}
};

struct Coach
{
	Game& game;

	explicit Coach(Game& game) :
		game{ game }
	{
		game.events.connect([](Event* e)
		{
			PlayerScored* ps = dynamic_cast<PlayerScored*>(e);
			if (ps && ps->goals_scored < 3)
				cout << "Coach says: Well done, " << ps->player_name << "!\n";
		});
	}
};

int main()
{
	Game game;
	Player player{ game, "Miyazaki" };
	Coach coach{ game };

	player.score();
	player.score();
	player.score();

	return 0;
}