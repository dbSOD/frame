#pragma once
#include <vector>
#include <memory>
#include "SMstruct.h"
/*
共享内存客户端（用于dll）
*/
class shareMemoryCli
{
public:
	shareMemoryCli(int num);
	~shareMemoryCli();

	bool openShareMemory();
	void destoryShareMemory();
	int getPidEmptyIndex();

public:
	_SM_ALL_SHARE_DATA *m_pSMAllData;
};

