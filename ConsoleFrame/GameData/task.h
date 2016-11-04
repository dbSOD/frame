#pragma once
#include "base.h"
/*
ÈÎÎñÀà
*/
class task :
	public base
{
public:
	task();
	virtual ~task();
	virtual bool init();
private:
	std::vector<std::shared_ptr<TASK_PROPERTY>> m_taskList;
};

