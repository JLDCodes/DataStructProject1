#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include "SmartArray.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"
// Operator to sort by title
bool operator < (cPerson const& lhs, cPerson const& rhs) {
	return lhs.first < rhs.first;
}

bool operator <= (cPerson const& lhs, cPerson const& rhs) {
	return lhs.first <= rhs.first;
}


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
	for (int i = 0; i < 100; i++) {
		personVec.addAtEnd(pGen->generateRandomPerson());
	}

	for (int i = 0; i < personVec.getSize(); i++) {
		std::cout << personVec.getAt(i)->first << " " << personVec.getAt(i)->middle << " " << personVec.getAt(i)->last << " " << personVec.getAt(i)->gender << " " <<personVec.getAt(i)->SIN << " " << personVec.getAt(i)->age << " " << personVec.getAt(i)->postalCode << "\n";
		std::cout << personVec.getAt(i)->getSnotifyUniqueUserID() << " " << personVec.getAt(i)->city << " " << personVec.getAt(i)->streetName << ",  " << personVec.getAt(i)->streetDirection << ", " << personVec.getAt(i)->streetType << " " << personVec.getAt(i)->streetNumber << "\n";
	}

	cMusicGenerator* mGen = new cMusicGenerator;
	mGen->LoadMusicInformation("hot_stuff_2.csv", error);

	for (int i = 0; i < mGen->artistVec.getSize()-1; i++) {
		std::cout << "Artist: " << mGen->cSongVec.getAt(i)->artist << " songName: " << mGen->cSongVec.getAt(i)->name << "\n";
	}
	
	std::cout << mGen->songIdVec.getSize() << "\n";

	cSong* song = mGen->getRandomSong();
	std::cout << song->artist << " " << song->name << "\n";

	cSong* song2 = mGen->findSong("3", "Britney Spears");
	std::cout << song2->artist << " " << song2->name << "\n";

	cSnotify* spotify = new cSnotify;

	spotify->AddUser(pGen->generateRandomPerson(), error);

	std::cout << spotify->personLibVec.getAt(0)->first << "\n";
	spotify->AddUser(pGen->generateRandomPerson(), error);
	spotify->DeleteUser(spotify->personLibVec.getAt(0)->getSnotifyUniqueUserID(), error);

	std::cout << spotify->personLibVec.getSize();

	spotify->AddSong(song, error);
	spotify->AddSong(song2, error);
	spotify->AddSong(mGen->getRandomSong(), error);
	spotify->AddSong(mGen->getRandomSong(), error);
	spotify->AddSong(mGen->getRandomSong(), error);
	std::cout << spotify->songLibVec.getAt(0)->getUniqueID() << "\n";
	std::cout << spotify->songLibVec.getAt(1)->getUniqueID() << "\n";
	std::cout << spotify->songLibVec.getAt(2)->getUniqueID() << "\n";
	std::cout << spotify->songLibVec.getAt(3)->getUniqueID() << "\n";
	std::cout << spotify->songLibVec.getAt(4)->getUniqueID() << "\n";
}

