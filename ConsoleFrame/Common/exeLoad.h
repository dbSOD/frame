#pragma once
#include<windows.h>  
#include "atlstr.h"  
#include <string>
//#include "string"  
#pragma comment(lib, "Kernel32.lib")  

class exeLoad
{
public:
	exeLoad(std::string filename);
	~exeLoad();

	STARTUPINFO si; //一些必备参数设置  
	PROCESS_INFORMATION pi; //必备参数设置结束  
	std::string filename;
};

