#include "cSong.h"
#include <random>

unsigned int cSong::m_NEXT_Snotify_UniqueSongID = 1;

cSong::cSong() {
	this->rating = 0;
	this->numberOfTimesPlayed = 0;

	
	this->uniqueID = cSong::m_NEXT_Snotify_UniqueSongID;
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1, 11);

	cSong::m_NEXT_Snotify_UniqueSongID += dist(rd);
}

unsigned int cSong::getUniqueID(void) {
	return this->uniqueID;
}


cSong::~cSong() {


}