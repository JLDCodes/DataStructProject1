#include <iostream>
#include <fstream>
#include <sstream>		
#include <string>
#include "SmartArray.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"

int main()
{
	cPersonGenerator* pGen =  new cPersonGenerator;
	std::string error = "Error!!!";
	pGen->LoadCensusFiles("yob1880.txt", "Names_2010Census.csv", "Street_Names.csv", error);


	SmartArray<cPerson*> personVec;
	for (unsigned int i = 0; i < 100; i++) {
		personVec.addAtEnd(pGen->generateRandomPerson());
	}

	for (unsigned int i = 0; i < personVec.getSize(); i++) {
		std::cout << personVec.getAt(i)->first << " " << personVec.getAt(i)->middle << " " << personVec.getAt(i)->last << " " << personVec.getAt(i)->gender << " " <<personVec.getAt(i)->SIN << " " << personVec.getAt(i)->age << " " << personVec.getAt(i)->postalCode << "\n";
		std::cout << personVec.getAt(i)->getSnotifyUniqueUserID() << " " << personVec.getAt(i)->city << " " << personVec.getAt(i)->streetName << ",  " << personVec.getAt(i)->streetDirection << ", " << personVec.getAt(i)->streetType << " " << personVec.getAt(i)->streetNumber << "\n";
	}

	cMusicGenerator* mGen = new cMusicGenerator;
	mGen->LoadMusicInformation("hot_stuff_2.csv", error);

	for (unsigned int i = 0; i < mGen->artistList.getSize()-1; i++) {
		std::cout << "Artist: " << mGen->cSongList.getAt(i)->artist << " songName: " << mGen->cSongList.getAt(i)->name << "\n";
	}
	
	std::cout << mGen->songIdVec.getSize() << "\n";

	cSong* song = mGen->getRandomSong();
	std::cout << song->artist << " " << song->name << "\n";

	cSong* song2 = mGen->findSong("3", "Britney Spears");
	std::cout << song2->getUniqueID() <<song2->artist << " " << song2->name << "\n";

	cSnotify* spotify = new cSnotify;

	spotify->AddUser(pGen->generateRandomPerson(), error);
	for (int i = 0; i < 100; i++) {
		spotify->AddUser(pGen->generateRandomPerson(), error);
	}

	std::cout << spotify->personLibVec.getAt(0)->first << "\n";
	spotify->AddUser(pGen->generateRandomPerson(), error);
	spotify->DeleteUser(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), error);

	std::cout << spotify->personLibVec.getSize() << "\n";

	spotify->AddSong(song, error);
	spotify->AddSong(song2, error);
	spotify->AddSong(mGen->getRandomSong(), error);
	spotify->AddSong(mGen->getRandomSong(), error);
	spotify->AddSong(mGen->getRandomSong(), error);
	std::cout << spotify->songLibVec.getAt(0)->getUniqueID() << spotify->songLibVec.getAt(0)->name <<"\n";
	std::cout << spotify->songLibVec.getAt(1)->getUniqueID() << spotify->songLibVec.getAt(1)->name <<"\n";
	std::cout << spotify->songLibVec.getAt(2)->getUniqueID() << spotify->songLibVec.getAt(2)->name<<"\n";
	std::cout << spotify->songLibVec.getAt(3)->getUniqueID() << spotify->songLibVec.getAt(3)->name<<"\n";
	std::cout << spotify->songLibVec.getAt(4)->getUniqueID() << spotify->songLibVec.getAt(4)->name<<"\n";

	spotify->DeleteSong(spotify->songLibVec.getAt(1)->getUniqueID(), error);
	std::cout << "\n\n";
	for (unsigned int i = 0; i < spotify->songLibVec.getSize(); i++) {
		std::cout << spotify->songLibVec.getAt(i)->getUniqueID() << spotify->songLibVec.getAt(i)->name << "\n";
	}

	spotify->AddSongToUserLibrary(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), song, error);
	std::cout << spotify->personLibVec.getAt(0)->personalSongLibVec.getAt(0)->name << "\n";
	spotify->RemoveSongFromUserLibrary(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), song->getUniqueID(), error);
	std::cout << spotify->personLibVec.getAt(0)->personalSongLibVec.getSize() << "\n";
	std::cout << "\n\n";
	spotify->AddSongToUserLibrary(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), song, error);
	std::cout << "user rating: " << spotify->personLibVec.getAt(0)->userRatingVec.getAt(0) << "\n";
	spotify->UpdateRatingOnSong(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), spotify->personLibVec.getAt(0)->personalSongLibVec.getAt(0)->getUniqueID(), 5);
	std::cout << "user rating: " << spotify->personLibVec.getAt(0)->userRatingVec.getAt(0) << "\n";

	std::cout << "number of times played " << spotify->personLibVec.getAt(0)->userSongsPlayedVec.getAt(0) << "\n";
	spotify->GetSong(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), spotify->personLibVec.getAt(0)->personalSongLibVec.getAt(0)->getUniqueID(), error);
	std::cout << "number of times played " << spotify->personLibVec.getAt(0)->userSongsPlayedVec.getAt(0) << "\n";

	unsigned int songRating;
	std::cout << spotify->GetCurrentSongRating(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), spotify->personLibVec.getAt(0)->personalSongLibVec.getAt(0)->getUniqueID(), songRating) << "\n";
	std::cout << "song rating: " << songRating << "\n";

	spotify->GetCurrentSongNumberOfPlays(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), spotify->personLibVec.getAt(0)->personalSongLibVec.getAt(0)->getUniqueID(), songRating);
	std::cout << songRating << "\n";

	std::cout << "\n\n";

	std::cout << spotify->personLibVec.getAt(0)->first << "\n";
	cPerson* bob = spotify->FindUserBySIN(spotify->personLibVec.getAt(0)->SIN);
	std::cout << bob->first << "\n";

	std::cout << "\n\n";
	cSong* pTheSongs;
	unsigned int size;
	for (unsigned int i = 0; i < 100; i++) {
		spotify->songLibVec.addAtEnd(mGen->getRandomSong());
	}

	for (unsigned int i = 0; i < 7; i++) {
		std::cout << spotify->songLibVec.getAt(i)->name << "\n";
	}
	for (unsigned int i = 0; i < 100; i++) {
		spotify->personLibVec.getAt(0)->personalSongLibVec.addAtEnd(spotify->songLibVec.getAt(i));
	}

	std::cout << "\n\n";
	spotify->GetUsersSongLibrary(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), pTheSongs, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << pTheSongs[i].name << "\n";
	}
	std::cout << "\n\n";
	spotify->GetUsersSongLibraryAscendingByTitle(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), pTheSongs, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << pTheSongs[i].name << "\n";
	}
	std::cout << "\n\n";
	spotify->GetUsersSongLibraryAscendingByArtist(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), pTheSongs, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << pTheSongs[i].artist << "\n";
	}
	std::cout << "\n\n";
	cPerson* peopleLib;
	spotify->AddUser(pGen->generateRandomPerson(), error);
	spotify->AddUser(pGen->generateRandomPerson(), error);
	spotify->AddUser(pGen->generateRandomPerson(), error);
	
	spotify->GetUsers(peopleLib, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << peopleLib[i].last << "\n";
	}
	std::cout << "\n\n";
	spotify->GetUsersByID(peopleLib, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << peopleLib[i].m_Snotify_UniqueUserID << "\n";
	}
	spotify->personLibVec.getAt(1)->first = spotify->personLibVec.getAt(0)->first;
	size = 0;
	cPerson* pepLib;
	spotify->FindUsersFirstName(spotify->personLibVec.getAt(0)->first, pepLib, size);
	//
	std::cout << "\n\n";
	for (unsigned int i = 0; i < size; i++) {
		std::cout << pepLib[i].first << " " << pepLib[i].last << "\n";
	}
	spotify->personLibVec.getAt(2)->last = spotify->personLibVec.getAt(0)->last;
	std::cout << "\n\n";
	spotify->FindUsersLastName(spotify->personLibVec.getAt(0)->last, peopleLib, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << peopleLib[i].first << " " << peopleLib[i].last << "\n";
	}
	spotify->personLibVec.getAt(2)->first = spotify->personLibVec.getAt(0)->first;
	std::cout << "\n\n";
	spotify->FindUsersFirstLastNames(spotify->personLibVec.getAt(0)->first, spotify->personLibVec.getAt(0)->last, peopleLib, size);
	for (unsigned int i = 0; i < size; i++) {
		std::cout << peopleLib[i].first << " " << peopleLib[i].middle << " " << peopleLib[i].last << "\n";
	}


}

