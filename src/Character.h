#pragma once

// �����ɫ���ԣ�����ֵ��������
class Character
{
public:
	float hp, atk;
	bool isdeath;
	Character(float hp, float atk);
	void modifyHp(float value);
	void modifyAtk(float value);
};

