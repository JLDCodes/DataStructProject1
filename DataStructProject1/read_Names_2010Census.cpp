#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
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

	//std::cout << "Number of names: " << pGen->getNumberOfNamesLoaded() << ", Number of surnames: " << pGen->getNumberOfSurnamesLoaded() << ", number of street names: " << pGen->getNumberOfStreetsLoaded() << "\n";
	//std::cout << "First: " << pGen->nameVec.getAt(0) << ", " << pGen->surnameVec.getAt(0) << ", " << pGen->streetNameVec.getAt(0) << "\n" ;

	//for (int i = 0; i < pGen->getNumberOfNamesLoaded(); i++) {
	//	std::cout << pGen->nameVec.getAt(i) << ", " << pGen->surnameVec.getAt(i) << ", " << pGen->streetNameVec.getAt(i) << "\n";
	//}
	// Open the file
	//std::ifstream namesFile("Street_Names.csv");
	//if ( ! namesFile.is_open() )
	//{
	//	std::cout << "Didn't open file" << std::endl;
	//	return -1;
	//}
;
// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
//
// - rank is how popular the last name is, like 1st, 2nd, etc.
// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
//            that someone is named "Smith"
	//
	////std::string theLine;

	////unsigned int lineCount = 0;
	////skip first entry column name
	////std::getline(namesFile, theLine);
	////store all the first names
	////SmartArray<std::string> streetNameVec;
	////SmartArray<std::string> streetTypeVec;
	////SmartArray<std::string> streetDirec;
	////while (std::getline(namesFile, theLine))
	////{
	////	lineCount++;
	////	std::stringstream ssLine(theLine);

	////	std::string token;
	////	unsigned int tokenCount = 0;
	////	while (std::getline(ssLine, token, ','))
	////	{
	////		if ( tokenCount == 1 )
	////		{
	////			streetNameVec.addAtEnd(token);
	////		}
	////		if (tokenCount == 2) {
	////			streetTypeVec.addAtEnd(token);
	////		}
	////		if (tokenCount == 3) {
	////			streetDirec.addAtEnd(token);
	////		}
	////		 Ignore the other parts of the line
	////		tokenCount++;
	////	}
	////}

	////std::cout << "Lines read = " << lineCount << std::endl;
	////for (int i = 0; i < streetNameVec.getSize(); i++) {
	////	std::cout << streetNameVec.getAt(i) << ",  " << streetNameVec.getAt(i) << ", " << streetNameVec.getAt(i)<<"\n";
	////}
	////return 0;
	//SmartArray<double> vector;
	//vector.addAtEnd(5);
	//vector.addAtEnd(4);
	//vector.addAtEnd(3);
	//vector.addAtEnd(2);
	//vector.addAtEnd(1);
	//std::cout << "before sorting: " << "\n";
	//for (int i = 0; i < 5; i++) {
	//	std::cout << vector.getAt(i) << std::endl;
	//}
	//std::cout << "after sorting: " << "\n";
	//vector.quickSort(0, vector.getSize() - 1);

	//for (int i = 0; i < 5; i++) {
	//	std::cout << vector.getAt(i) << std::endl;
	//}
	//SmartArray<std::string> stringVec;
	//stringVec.addAtEnd("z");
	//stringVec.addAtEnd("d");
	//stringVec.addAtEnd("q");
	//stringVec.addAtEnd("a");

	//std::cout << "before sorting: " << "\n";
	//for (int i = 0; i < 5; i++) {
	//	std::cout << stringVec.getAt(i) << std::endl;
	//}

	//stringVec.quickSort(0, stringVec.getSize());

	//std::cout << "after sorting: " << "\n";
	//for (int i = 0; i < 5; i++) {
	//	std::cout << stringVec.getAt(i) << std::endl;
	//}


	//SmartArray<cPerson*> personVec;
	//cPerson* bob = new cPerson();
	//bob->first = "bob";
	//cPerson* dan = new cPerson();
	//dan->first = "dan";
	//cPerson* chloe = new cPerson();
	//chloe->first = "chloe";
	//cPerson* jill = new cPerson();
	//jill->first = "jill";
	//cPerson* kek = new cPerson();
	//kek->first = "kek";
	//personVec.addAtEnd(chloe);
	//personVec.addAtEnd(dan);
	//personVec.addAtEnd(bob);
	//personVec.addAtEnd(jill);
	//personVec.addAtEnd(kek);
	//std::cout << "before sorting: " << std::endl;
	//for (int i = 0; i < personVec.getSize(); i++) {
	//	std::cout << personVec.getAt(i)->first << "\n";
	//}
	//personVec.quickSort(0, personVec.getSize()-1);
	//std::cout << "after sorting: " << std::endl;
	//for (int i = 0; i < personVec.getSize(); i++) {
	//	std::cout << personVec.getAt(i)->first << "\n";
	//}

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

	for (unsigned int i = 0; i < mGen->artistVec.getSize()-1; i++) {
		std::cout << "Artist: " << mGen->cSongVec.getAt(i)->artist << " songName: " << mGen->cSongVec.getAt(i)->name << "\n";
	}
	
	std::cout << mGen->songIdVec.getSize() << "\n";

	cSong* song = mGen->getRandomSong();
	std::cout << song->artist << " " << song->name << "\n";

	cSong* song2 = mGen->findSong("3", "Britney Spears");
	std::cout << song2->getUniqueID() <<song2->artist << " " << song2->name << "\n";

	cSnotify* spotify = new cSnotify;

	spotify->AddUser(pGen->generateRandomPerson(), error);

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
	for (unsigned int i = 0; i < 5; i++) {
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

}

