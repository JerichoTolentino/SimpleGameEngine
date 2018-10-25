#pragma once
#include "../entities/DynamicEntity.h"
#include "../terrains/Terrain.h"
#include "../display/window.h"

class Character
{
private:
	int level;
	int health;
	int mana;
	int stamina;
	std::string name;
	std::string type;
	DynamicEntity *entity;
	//TODO: Inventory *inventory;
	//TODO: AbilitySet *abilities;
public:
	Character();
	virtual ~Character();

	Character(int lvl, int hp, int mp, int sp, std::string n, std::string t, DynamicEntity *e);

	int getLevel() const;
	int getHealth() const;
	int getMana() const;
	int getStamina() const;
	std::string getName() const;
	std::string getType() const;
	DynamicEntity* getEntity() const;

	void setLevel(int lvl);
	void setHealth(int hp);
	void setMana(int mp);
	void setStamina(int sp);
	void setName(std::string n);
	void setType(std::string t);
	void setEntity(DynamicEntity *e);

	void move(Window &window, Terrain *terrain);
	//TODO: Add relevant methods...
};

