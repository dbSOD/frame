#pragma once
/*
所有对象类的基类
*/
#include <string>

class base
{
public:
	base();
	virtual ~base();
	std::string errorString();
	void setErrorString(std::string);
	virtual bool init() = 0;
private:
	std::string m_errorString;
};

