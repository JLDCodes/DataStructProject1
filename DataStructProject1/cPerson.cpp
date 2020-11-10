#include "cPerson.h"
#include <random>
// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

cPerson::cPerson()
{
	// In here, set the default information
	this->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
	this->streetNumber = 0;
	this->age = -1;
	this->SIN = 0;

	//this->
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1, 11);
	// Generate unique Snotify ID
	this->m_Snotify_UniqueUserID = cPerson::m_NEXT_Snotify_UniqueUSerID;
	// Increment for next created user by a small random amount 
	
	cPerson::m_NEXT_Snotify_UniqueUSerID += dist(rd);
}
unsigned int cPerson::getSnotifyUniqueUserID(void) {
	return m_Snotify_UniqueUserID;
}
// The 1st Snotify user will have ID: 10,000,000
// static 
unsigned int cPerson::m_NEXT_Snotify_UniqueUSerID = 10000000;

cPerson::~cPerson()
{
	
}

std::string cPerson::getGenderAsString(void)
{
	switch (this->gender)
	{
	case cPerson::MALE:
		return "MALE";
		break;
	case cPerson::FEMALE:
		return "FEMALE";
		break;
	case cPerson::NON_BINARY:
		return "NON_BINARY";
		break;
	case cPerson::RATHER_NOT_SAY_UNKNOWN:
		return "RATHER_NOT_SAY_UNKNOWN";
		break;
//	default:
//		break;
	}

	// This should never happen
//	return "RATHER_NOT_SAY_UNKNOWN";
	return "OMG! CALL THE DEV TEAM!! SOMEONE SCREWED UP!!!";
}