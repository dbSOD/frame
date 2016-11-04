#pragma once
#include "SMstruct.h"
#include <memory>
#include <vector>
/*
共享内存服务端（用于控制台）
*/
class shareMemorySer
{
public:
	shareMemorySer(int num);
	~shareMemorySer();

	bool createShareMemory();
	void destoryShareMemory();

private:
	_SM_ALL_SHARE_DATA *m_pSMAllData;
};

