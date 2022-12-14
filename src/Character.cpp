#include "Character.h"

Character::Character(float hp, float atk)
{
	this->hp = hp;
	this->atk = atk; 
	isdeath = (hp <= 0);
}

void Character::modifyHp(float value)
{
	hp += value;
	if (hp <= 0)
		isdeath = true;
}

void Character::modifyAtk(float value)
{
	atk += value;
}