#pragma once
#include "base.h"
/*
人物类
一般包含具体的人物属性等
*/
class role :
	public base
{
public:
	role();
	virtual ~role();
	virtual bool init();

private:
	ROLE_PROPERTY m_roleproperty;
};

