#pragma once

// 管理角色属性：生命值，攻击力
class Character
{
public:
	float hp, atk;
	bool isdeath;
	Character(float hp, float atk);
	void modifyHp(float value);
	void modifyAtk(float value);
};

