#include "monster.h"


monster::monster()
{
}


monster::~monster()
{
}

bool monster::init()
{
	
	try{
		std::shared_ptr<MONSTER_PROPERTY> temp(new MONSTER_PROPERTY);
		temp->szpName = (char*)(0x5000);
		m_monsterList.push_back(temp);
	}
	catch(...)
	{
		return false;
	}

	

	return true;
}

std::string monster::message()
{
	std::stringstream ss;
	for (int i = 0; i != m_monsterList.size(); i++)
	{
		ss << "¹ÖÎïÃû×Ö£º" << m_monsterList.at(i)->szpName << std::endl;
	}
	return ss.str();
}
