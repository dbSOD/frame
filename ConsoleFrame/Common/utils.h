#pragma once

#ifndef SECURITY_WIN32
#define  SECURITY_WIN32
#endif // !SECURITY_WIN32


#include <mutex>
#include <memory>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <Psapi.h>
#include <fstream>
#include <ctime>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <list>
#pragma comment(lib , "Psapi.lib")
/*
工具类
*/
class tools
{
public:
	static tools* getInstance();
	~tools();
	void message(char* fmt, ...);
	bool improveProcPriv();
	DWORD findPattern(unsigned long startAddrSize, DWORD fileSize, unsigned char* pattern, char mask[]);
	MODULEINFO getModuleInfo(const char* moduleName);
	bool log2file(std::string fileName, std::string data, std::ios_base::open_mode _model = std::ios::app);
	bool read(DWORD _addr, unsigned char* _data, int _size);
	bool write(DWORD _addr, unsigned char* _data, int _size);
	bool byte2hex(BYTE src, char* desc);
	bool lower2upper(char& ch);
	bool hexstr2upper(char* src);
	char hex2byte(const char& ch1, const char& ch2);
	bool bytes2hexstr(BYTE* src, DWORD ndSize, char* desc); //字节数组到hex数组的转换 
	bool hexstr2bytes(char* src, char* desc); //hex字符串到字节数组的转换
	bool fileIsexist(std::string fileName);
public:
	tools();
	tools(const tools&);
	tools& operator= (const tools&);
	static tools* m_pInstance;
	static std::mutex m_mutex;

};