// shareMemTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shareMemoryCli.h"
#include <iostream>
#include <string>
#pragma comment(lib, "Common.lib")
int main()
{
	//初始化共享内存

	shareMemoryCli shareCli(MORE_OPEN_NUMBER);
	
	if (!shareCli.openShareMemory())
	{
		std::cout << "打开共享内存失败！" << std::endl;
	}
	
	std::cout << GetCurrentProcessId() << std::endl;

	int index = shareCli.getPidEmptyIndex();
	shareCli.m_pSMAllData->m_sm_data[index].ndPid = GetCurrentProcessId();
	//shareCli.m_pSMAllData->m_sm_data[index]
	if (!shareCli.m_pSMAllData->m_sm_data[index].userName.empty() && !shareCli.m_pSMAllData->m_sm_data[index].passWord.empty())
	{
		std::cout <<"账号：" <<shareCli.m_pSMAllData->m_sm_data[index].userName << " , 密码:" << shareCli.m_pSMAllData->m_sm_data[index].passWord << std::endl;
	}

	getchar();
	return 0;
}

