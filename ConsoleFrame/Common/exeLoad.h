#pragma once
#include<windows.h>  
#include "atlstr.h"  
#include <string>
#pragma comment(lib, "Kernel32.lib")  

/*
加载一个外部的exe
*/
class exeLoad
{
public:
	exeLoad(std::string filename);
	~exeLoad();

	STARTUPINFO si; //一些必备参数设置  
	PROCESS_INFORMATION pi; //必备参数设置结束  
};

