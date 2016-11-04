#pragma once
#include <windows.h>

//人物属性
struct ROLE_PROPERTY
{
	ROLE_PROPERTY();
	~ROLE_PROPERTY();
	
	char* szpName;
	DWORD ndCurHp;
	DWORD ndMaxHp;

};

//周围对象
struct MONSTER_PROPERTY 
{
	MONSTER_PROPERTY();
	~MONSTER_PROPERTY();

	char* szpName;
};

//技能对象
struct SKILL_PROPERTY 
{
	SKILL_PROPERTY();
	~SKILL_PROPERTY();

	char* szpName;
};

//任务对象
struct TASK_PROPERTY
{
	TASK_PROPERTY();
	~TASK_PROPERTY();

	char* szpName;
};