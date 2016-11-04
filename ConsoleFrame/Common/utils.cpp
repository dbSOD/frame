#include "utils.h"

tools* tools::m_pInstance = nullptr;
std::mutex tools::m_mutex;
/*
函数功能：
单例模式指针获取
返回值：this指针，指向工具类
*/
tools* tools::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_mutex.lock();
		if (nullptr == m_pInstance)
		{
			m_pInstance = new tools;
		}
		m_mutex.unlock();
	}
	return m_pInstance;
}

tools::~tools()
{

}

tools::tools()
{

}

tools::tools(const tools&)
{

}

tools& tools::operator=(const tools&)
{
	return *this;
}


/*
函数功能：打印调试信息
参数1：数据格式
参数2：具体可变的参数
返回值：无
*/
void tools::message(char* fmt, ...)
{
	__try{
		char szbufFormat[0x1000];//字符串缓冲区，为vsprintf_s准备
		char szBufFormat_Game[0x1000] = "HXL:";//多8字节是为了加Game这个前缀
		va_list argList;
		va_start(argList, fmt);//参数列表初始化
		vsprintf_s(szbufFormat, fmt, argList);
		strcat_s(szBufFormat_Game, szbufFormat);//追加字符串
		OutputDebugString(szBufFormat_Game);
		va_end(argList);//清理工作
	}
	__except (1)
	{
		return;
	}
}
/*
函数功能：提升权限
返回值：BOOL 
*/
bool tools::improveProcPriv()
{
	HANDLE token;
	//提升权限
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
	{
		return false;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		return false;
	}
	CloseHandle(token);
	return true;
}

/*
函数功能：查找特征码
参数1：开始地址
参数2：地址大小
参数3：特征码
参数4：特征码掩码
返回值：特征码的开始地址
*/
DWORD tools::findPattern(DWORD startAddress, DWORD fileSize, unsigned char* pattern, char mask[])
{
	DWORD pos = 0;
	int searchLen = strlen(mask) - 1;
	//从内存内逐个字节进行比较
	for (DWORD retAddress = startAddress; retAddress < startAddress + fileSize; retAddress++)
	{
		//判断当前地址是否有效
		if (IsBadReadPtr((const void *)retAddress, 1))
		{
			pos = 0;
			continue;
		}
		if (*(PBYTE)retAddress == pattern[pos] || mask[pos] == '?')
		{
			if (mask[pos + 1] == '\0')
			{
				return (retAddress - searchLen);
			}

			pos++;
		}
		else
		{
			pos = 0;
		}
	}
	return NULL;
}
/*
函数功能：返回模块信息
参数：模块名字
返回值：模块信息
*/
MODULEINFO tools::getModuleInfo(const char* moduleName)
{
	MODULEINFO moudleInfo = { NULL };
	HMODULE hMoudle = GetModuleHandle(moduleName);
	if (hMoudle)
	{
		GetModuleInformation(GetCurrentProcess(), hMoudle, &moudleInfo, sizeof(MODULEINFO));
	}
	return moudleInfo;
}
/*
函数功能：记录日志文件
参数1：文件名
参数2：数据
参数3：打开模式
返回值：BOOL
*/
bool tools::log2file(std::string fileName, std::string data, std::ios_base::open_mode _model/*= std::ios::app*/)
{
	std::ofstream fout;
	fout.open(fileName, _model);
	if (!fout)
	{
		return false;
	}
	std::stringstream ss;
	time_t nowTime = time(NULL);
	ss << "time: " << nowTime<<" ";
	fout << ss.str() <<data << std::endl;
	fout.close();
	return true;
}
/*
函数功能：写内存字节集
参数1: 内存地址
参数2：字节集
参数3：尺寸
返回值：BOOL
*/
bool tools::write(DWORD _addr, unsigned char* _data, int _size)
{
	if (!improveProcPriv())
	{
		return false;
	}
	DWORD oldProtect = 0;
	if (!VirtualProtect((void*)_addr, _size, PAGE_READWRITE, &oldProtect))
	{
		tools::getInstance()->message("erroe1\n");
		return false;
	}
	memcpy((void*)_addr, _data, _size);
	if (!VirtualProtect((void*)_addr, _size, oldProtect, &oldProtect))
	{
		tools::getInstance()->message("erroe1\n");
		return false;
	}
	return  true;
}
/*
函数功能：读内存字节集
参数1: 内存地址
参数2：字节集
参数3：尺寸
返回值：BOOL
*/
bool tools::read(DWORD _addr, unsigned char* _data, int _size)
{
	unsigned long oldProtect = 0;
	if ( S_OK != VirtualProtect((void*)_addr, _size, PAGE_READONLY, &oldProtect))
	{
		return false;
	}
	memcpy((void*)_data, (void*)_addr, _size);
	if (S_OK !=VirtualProtect((void*)_addr, _size, oldProtect, 0))
	{
		return false;
	}
	return  true;
}

bool tools::byte2hex(BYTE src, char* desc)
{
	byte low = 0, high = 0;
	//取高地位 低位取余数
	low = src % 16;
	high = src / 16;

	if (high > 9)
	{
		//判断高位为A -F
		desc[0] = 'A' + high - 10;
	}
	else
	{
		desc[0] = '0' + high;
	}

	//对低位进行赋值
	if (low > 9)
	{
		desc[1] = 'A' + low - 10;
	}
	else
	{
		desc[1] = '0' + low;
	}
	desc[2] = ',';
	desc[3] = '\0';
	return true;
}

bool tools::lower2upper(char& ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch = ch + 'A' - 'a';
	}
	return true;
}

bool tools::hexstr2upper(char* src)
{
	DWORD ndLen = strlen(src);
	for (DWORD i = 0; i != ndLen; i++)
	{
		lower2upper(src[i]);
	}
	return true;
}

char tools::hex2byte(const char& high, const char& low)
{
	int result = 0;

	//如果高位为数字
	//计算方法就是   high - '0'
	if (high >= '0' && high <= '9')
	{
		result = high - '0';
	}
	else if (high >= 'A' && 'F')
	{
		//如果高位为字母
		//计算方法Wie  high - 'A' + 10
		result = high - 'A' + 10;
	}
	else
	{
		return -1;
	}
	//低位计算方法
	if (low >= '0' && low <= '9')
	{
		return result * 16 + low - '0';
	}
	else if (low >= 'A' && low <= 'F')
	{
		return result * 16 + low - 'A' + 10;
	}
	else
	{
		return -1;
	}
}

bool tools::bytes2hexstr(BYTE* src, DWORD ndSize, char* desc)
{

	//首先是将所有字符转化为大写字母
	__try{

		for (int i = 0; i != ndSize; i++)
		{
			byte2hex(src[i], &desc[i * 3]);
		}
	}
	__except (1)
	{

		tools::getInstance()->message("字节转换异常！\n");
	}
	//DWORD ndLen = strlen(src);

	return hexstr2upper(desc);
}

bool tools::hexstr2bytes(char* src, char* desc)
{
	hexstr2upper(src);
	DWORD ndLen = strlen(src);
	for (int i = 0; i != ndLen; i++)
	{
		desc[i] = hex2byte(src[i * 2], src[i * 2 + 1]);
	}
	return hexstr2upper(desc);
}

/*
函数功能：判断文件是否存在
参数1：文件名
返回值：bool
*/
bool tools::fileIsexist(std::string fileName)
{
	std::fstream ss;
	ss.open(fileName,std::ios::in);
	bool result;
	if (ss)
		result = true;
	else
		result = false;
	ss.close();
	return result;
}

