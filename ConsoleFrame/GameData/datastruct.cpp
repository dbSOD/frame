#include "datastruct.h"



ROLE_PROPERTY::ROLE_PROPERTY()
{
	szpName = nullptr;
	ndCurHp = 0;
	ndMaxHp = 0;
}

ROLE_PROPERTY::~ROLE_PROPERTY()
{
	if (!szpName)
	{
		delete szpName;
	}
}

MONSTER_PROPERTY::MONSTER_PROPERTY()
{
	szpName = nullptr;
}

MONSTER_PROPERTY::~MONSTER_PROPERTY()
{
	if (!szpName)
	{
		delete szpName;
	}
}

SKILL_PROPERTY::SKILL_PROPERTY()
{
	szpName = nullptr;
}

SKILL_PROPERTY::~SKILL_PROPERTY()
{
	if (!szpName)
	{
		delete szpName;
	}
}
