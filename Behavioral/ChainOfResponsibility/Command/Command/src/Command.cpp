#include <string>
#include <iostream>
using namespace std;

struct Creature
{
    string name;
    int attack, defense;

    Creature(const string& name, const int attack, const int defense) :
        name{ name },
        attack{ attack },
        defense{ defense }
    {}

    friend ostream& operator<<(ostream& os, const Creature& obj)
    {
        return os
            << "Name:\t" << obj.name
            << "\n--Attack:\t" << obj.attack
            << "\n--Defense:\t" << obj.defense << "\n";
    }
};

class CreatureModifier
{
    CreatureModifier* next{ nullptr };

protected:
    Creature& creature;

public:
    explicit CreatureModifier(Creature& creature) :
        creature{ creature }
    {}
    virtual ~CreatureModifier() = default;

    void add(CreatureModifier* cm)
    {
        if (next) next->add(cm);
        else next = cm;
    }

    virtual void handle()
    {
        if (next) next->handle();
    }
};

struct NoBonusesModifier : public CreatureModifier
{
    explicit NoBonusesModifier(Creature& creature) :
        CreatureModifier{ creature }
    {}

    void handle() override {}
};

struct DoubleAttackModifier : public CreatureModifier
{
    explicit DoubleAttackModifier(Creature& creature) :
        CreatureModifier{ creature }
    {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

struct IncreaseDefenseModifier : public CreatureModifier
{
    explicit IncreaseDefenseModifier(Creature& creature) :
        CreatureModifier{ creature }
    {}

    void handle() override
    {
        if (creature.attack <= 2)
            creature.defense++;
        CreatureModifier::handle();
    }
};

int main()
{
    Creature goblin{ "Goblin", 1, 1 };
    cout << goblin << endl;

    CreatureModifier root{ goblin };
    //NoBonusesModifier nb{ goblin };
    DoubleAttackModifier am1{ goblin };
    DoubleAttackModifier am2{ goblin };
    IncreaseDefenseModifier dm1{ goblin };

    //root.add(&nb);
    root.add(&am1);
    root.add(&am2);
    root.add(&dm1);

    root.handle();
    cout << goblin << endl;

    return 0;
}