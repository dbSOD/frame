#pragma once
#include <windows.h>
#include <vector>
#pragma pack(4)

#define  FILE_MAP_NAME	 "xxooyy"
#define  MORE_OPEN_NUMBER 5
//共享内存
typedef struct _SM_SHARE_DATA
{
	DWORD ndPid; //进程pid
	std::string userName;
	std::string passWord;
}SM_SHARE_DATA;

struct _SM_ALL_SHARE_DATA
{
	SM_SHARE_DATA m_sm_data[MORE_OPEN_NUMBER];
};



#pragma  pack()