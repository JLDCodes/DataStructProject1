#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cSong.h"
#include "SmartArray.h"
#include "cLinkedList.h"
class cMusicGenerator
{
public:
	cLinkedList<std::string> artistList;
	cLinkedList<std::string> songList;
	cLinkedList<cSong*> cSongList;
	SmartArray<std::string> songIdVec;
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);
};

#endif
