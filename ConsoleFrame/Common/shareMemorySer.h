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
	//查找pid\用户名为空为空的内存块
	int findPidEmptyIndex();
	//清空某一块内存
	void clearMemOfIndex(int index);
public:
	_SM_ALL_SHARE_DATA *m_pSMAllData;
};

