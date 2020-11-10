#include "cSnotify.h"


cSnotify::cSnotify() {

}
cSnotify::~cSnotify() {

}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString) {
	for (int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			personLibVec.removeFromVec(i);
			return true;
		}
	}
	return false;
}

// All these return true if they work, false if not (for any reason)
	// You can add some error information to the by referenece error string, if you want. 
bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString) {
	personLibVec.addAtEnd(pPerson);
	return true;
}

// This will overwrite the data contained in user 
// NOTE: It "finds" the user by matching BOTH the "unique Snofity ID" AND the "SIN" 
//        (Social Insurance Number)
// So if either of these don't match (or aren't found) then it reutrns false. 
bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString) {
	for (int i = 0; i < personLibVec.getSize(); i++) {
		if (pPerson->SIN == personLibVec.getAt(i)->SIN && pPerson->getSnotifyUniqueUserID() == personLibVec.getAt(i)->getSnotifyUniqueUserID()) {
			personLibVec.pArray_[i] = pPerson;
			return true;
		}
	}
	return false;
}

// This returns a COPY of the users library, in the form of a regular dynamic array.
bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// The caller would do something like this (assume the user ID = 28472382)
	//
	//	cSong* pTheSongs = 0;
	//	unsigned int arraySize = 0;
	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
	// 
	// Inside this method, you'd do something like this:

	// TODO: Find that user... 

	// Alloate a heap based array to hold all the songs...

	//	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
	//	pCopyOfLibrary = new cSong[sizeOfLibary];

	// The array and the size of the array are "returned" by reference to the caller. 

	// TODO: Copy all the songs over

	return true;
}


bool cSnotify::AddSong(cSong* pSong, std::string& errorString) {
	songLibVec.addAtEnd(pSong);
	return true;
}

// This finds a match, based on the "unique ID", and overwrites the data. 
bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString) {
	for (int i = 0; i < songLibVec.getSize(); i++) {
		if (pSong->getUniqueID() == songLibVec.getAt(i)->getUniqueID()) {
			songLibVec.pArray_[i] = pSong;
			return true;
		}
	}
	return false;
}