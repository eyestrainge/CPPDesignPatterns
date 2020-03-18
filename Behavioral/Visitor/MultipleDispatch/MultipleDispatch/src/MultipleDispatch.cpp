#include "Model.hpp"

struct GameObject;
void collide(GameObject& first, GameObject& second);

struct GameObject
{
	virtual ~GameObject() = default;
	
	virtual type_index type() const = 0;
	virtual void collide(GameObject& other)
	{ 
		::collide(*this, other);
	}
};

template <typename T>
struct GameObjectImpl : GameObject
{
	type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet> {};
struct Asteroid : GameObjectImpl<Asteroid> {};
struct Spaceship : GameObjectImpl<Spaceship> {};
struct ArmedSpaceship : Spaceship
{
	type_index type() const override
	{
		return typeid(ArmedSpaceship);
	}
};

void asteroid_planet() { cout << "Asteroid burns up in atmosphere\n"; }
void spaceship_planet() { cout << "Spaceship lands on planet\n"; }
void asteroid_spaceship() { cout << "Asteroid hits and destroys spaceship\n"; }
void asteroid_armed_spaceship() { cout << "Spaceship shoots asteroid\n"; }

map<pair<type_index, type_index>, void(*)(void)> outcomes{
	{ { typeid(Asteroid), typeid(Planet) }, asteroid_planet },
	{ { typeid(Spaceship), typeid(Planet) }, spaceship_planet },
	{ { typeid(Asteroid), typeid(Spaceship) }, asteroid_spaceship },
	{ { typeid(Asteroid), typeid(ArmedSpaceship) }, asteroid_armed_spaceship }
};

void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end())
		{
			cout << "Objects pass each other harmlessly\n";
			return;
		}
	}
	it->second();
}

int main()
{
	Planet planet;
	Asteroid asteroid;
	Spaceship spaceship;
	ArmedSpaceship armed_spaceship;

	collide(planet, asteroid);
	collide(planet, spaceship);	
	collide(asteroid, spaceship);
	collide(asteroid, armed_spaceship);
	//collide(planet, planet);
	planet.collide(planet);

	return 0;
}