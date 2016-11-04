#pragma once
#include "base.h"
/*
¼¼ÄÜÀà
*/
class skill :
	public base
{
public:
	skill();
	virtual ~skill();


private:
	std::vector<std::shared_ptr<SKILL_PROPERTY>> m_skillList;
};

