#include "Character.h"



Character::Character()
{
	level = 1;
	health = 50;
	mana = 50;
	stamina = 50;
	name = "Character";
	type = "General";
	entity = new DynamicEntity;
}


Character::~Character()
{
	//delete inventory;
	//delete abilities;
	delete entity;
}

Character::Character(int lvl, int hp, int mp, int sp, std::string n, std::string t, DynamicEntity *e)
{
	level = lvl;
	health = hp;
	mana = mp;
	stamina = sp;
	name = n;
	type = t;
	entity = e;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealth() const
{
	return health;
}

int Character::getMana() const
{
	return mana;
}

int Character::getStamina() const
{
	return stamina;
}

std::string Character::getName() const
{
	return name;
}

std::string Character::getType() const
{
	return type;
}

DynamicEntity * Character::getEntity() const
{
	return entity;
}

void Character::setLevel(int lvl)
{
	level = lvl;
}

void Character::setHealth(int hp)
{
	health = hp;
}

void Character::setMana(int mp)
{
	mana = mp;
}

void Character::setStamina(int sp)
{
	stamina = sp;
}

void Character::setName(std::string n)
{
	name = n;
}

void Character::setType(std::string t)
{
	type = t;
}

void Character::setEntity(DynamicEntity *e)
{
	entity = e;
}

void Character::move(Window & window, Terrain *terrain)
{

}
