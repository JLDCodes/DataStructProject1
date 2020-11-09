#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cSong.h"
#include "SmartArray.h"

class cMusicGenerator
{
public:
	SmartArray<std::string> songNameVec;
	SmartArray<std::string> artistVec;
	SmartArray<std::string> songIdVec;
	SmartArray<cSong*> cSongVec;
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
