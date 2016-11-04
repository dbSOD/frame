#pragma once
#include "base.h"
/*
周围对象类：
包含NPC, 怪物，地面物品等
*/

class monster :
	public base
{
public:
	monster();
	virtual ~monster();

	virtual bool init();
	virtual std::string message();
private:
	std::vector<std::shared_ptr<MONSTER_PROPERTY>> m_monsterList;
};

