#pragma once
#include "cMusicGenerator.h"
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include <iostream>
#include <random>

cMusicGenerator::cMusicGenerator() {

}

cMusicGenerator::~cMusicGenerator() {

}


bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString) {

	
	std::ifstream musicFile(musicFileName);
	if (!musicFile.is_open())
	{
		std::cout << "Failed to open file: " << musicFileName << std::endl;
		std::cout << errorString << std::endl;
		return false;
	}
	
	std::string theLine;
	// skip first line in file 
	std::getline(musicFile, theLine);


	while (std::getline(musicFile, theLine))
	{
		std::stringstream ssLine(theLine);
		std::string token;
		unsigned int tokenCount = 0;
		std::string holdSongName;
		std::string holdArtist;
		cSong* songToAdd = new cSong;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 3)
			{
				if (token[0] == '"') {
					break;
				}
				holdSongName =token;
			}
			if (tokenCount == 4) {
				if (token[0] == '"') {
					break;
				}
				holdArtist =token;
			}
			if (tokenCount == 5) {
				if (songIdVec.addAtEndNoDuplicates(token) == true) {
					songToAdd->artist = holdArtist;
					songToAdd->name = holdSongName;
					cSongList.insert(songToAdd);
					artistList.insert(holdArtist);
					songList.insert(holdSongName);
				}
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}



	return true;
}

cSong* cMusicGenerator::getRandomSong(void) {
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, cSongList.getSize()-1);
	int songId = dist(rd);
	while (true){
		if (releaseList.addAtEndNoDuplicates(cSongList.getAt(songId)) == true) {
			return cSongList.getAt(songId);
		}
		songId = dist(rd);
	}
	
	
}

// Returns 0, NULL, or nullptr if no song is found
// This must be an EXACT MATCH for what's in the billboard100 file. 
// So case sensitive, etc. 
cSong* cMusicGenerator::findSong(std::string songName, std::string artist) {
	
	for (unsigned int i = 0; i < cSongList.getSize(); i++) {
		if (cSongList.getAt(i)->name == songName && cSongList.getAt(i)->artist == artist) {
			return cSongList.getAt(i);
		}
	}
	return nullptr;
}