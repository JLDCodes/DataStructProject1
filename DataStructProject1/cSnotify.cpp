#include "cSnotify.h"




cSnotify::cSnotify() {

}
cSnotify::~cSnotify() {

}
//Removes user from the user libarary (which is a smart array)
bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
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
	if (pPerson == nullptr) {
		return false;
	}
	personLibVec.addAtEnd(pPerson);
	return true;
}

// This will overwrite the data contained in user 
// NOTE: It "finds" the user by matching BOTH the "unique Snofity ID" AND the "SIN" 
//        (Social Insurance Number)
// So if either of these don't match (or aren't found) then it reutrns false. 
bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (pPerson->SIN == personLibVec.getAt(i)->SIN && pPerson->getSnotifyUniqueUserID() == personLibVec.getAt(i)->getSnotifyUniqueUserID()) {
			personLibVec.pArray_[i] = pPerson;
			return true;
		}
	}
	return false;
}

// Add song to song libarary, no dubplicates allowed here
bool cSnotify::AddSong(cSong* pSong, std::string& errorString) {
	
	if (pSong == nullptr) {
		return false;
	}
	songLibVec.addAtEndNoDuplicates(pSong);
	return true;
}

// This finds a match, based on the "unique ID", and overwrites the data. 
bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString) {
	for (unsigned int i = 0; i < songLibVec.getSize(); i++) {
		if (pSong->getUniqueID() == songLibVec.getAt(i)->getUniqueID()) {
			songLibVec.pArray_[i] = pSong;
			return true;
		}
	}
	return false;
}

//finds unique song id and then removes that song from the song libarary (smart array)
bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString) {
	for (unsigned int i = 0; i < songLibVec.getSize(); i++) {
		if (songLibVec.getAt(i)->getUniqueID() == UniqueSongID) {
			songLibVec.removeFromVec(i);
			return true;
		}
	}
	return false;
}

// This associates a particular song with a particular user. 
// (returns true if the song is already there)
bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString) {
	for (unsigned int i = 0; i < songLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			// PARALLEL SMART ARRAYS used to keep personal ratings and times played 
			personLibVec.getAt(i)->personalSongLibVec.addAtEndNoDuplicates(pNewSong);
			personLibVec.getAt(i)->userRatingVec.addAtEnd(0);
			personLibVec.getAt(i)->userSongsPlayedVec.addAtEnd(0);
			return true;
		}
	}
	return false;
}


// removes song from libarary (smart array) and also removes it from the parallel rating and times played smart arrays
bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				if (personLibVec.getAt(i)->personalSongLibVec.getAt(k)->getUniqueID() == SnotifySongID) {
					personLibVec.getAt(i)->personalSongLibVec.removeFromVec(k);
					personLibVec.getAt(i)->userRatingVec.removeFromVec(k);
					personLibVec.getAt(i)->userSongsPlayedVec.removeFromVec(k);
					return true;
				}
			}	
		}
	}
	return false;
}

// access paralel array in cPerson
bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				if (personLibVec.getAt(i)->personalSongLibVec.getAt(k)->getUniqueID() == songUniqueID) {
					personLibVec.getAt(i)->userRatingVec.update(k, newRating);
					return true;
				}
			}
		}
	}
	return false;
}

//finds song based on song ID returns a pointer to the song
cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				if (personLibVec.getAt(i)->personalSongLibVec.getAt(k)->getUniqueID() == songUniqueID) {
					personLibVec.getAt(i)->userSongsPlayedVec.update(k, personLibVec.getAt(i)->userSongsPlayedVec.getAt(k)+1);
					return personLibVec.getAt(i)->personalSongLibVec.getAt(k);
				}
			}
		}
	}
	return nullptr;
}

// Note that the songRating is "returned" by reference. 
	// If it can't find a match (i.e. returns false), then the rating isn't valid. 
bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				if (personLibVec.getAt(i)->personalSongLibVec.getAt(k)->getUniqueID() == songUniqueID) {
					songRating = personLibVec.getAt(i)->userRatingVec.getAt(k);
					return true;
				}
			}
		}
	}
	return false;
}

// access parallel cPerson smart array for number of plays
bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				if (personLibVec.getAt(i)->personalSongLibVec.getAt(k)->getUniqueID() == songUniqueID) {
					numberOfPlays = personLibVec.getAt(i)->userSongsPlayedVec.getAt(k);
					return true;
				}
			}
		}
	}
	return false;
}

// goes through user lib and searches for matching sin. returns a pointer to the person with the sin
cPerson* cSnotify::FindUserBySIN(unsigned int SIN) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->SIN == SIN) {
			return personLibVec.getAt(i);
		}
	}
	return nullptr;
}

// find user by snotify id, returns a pointer to the user
cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == SnotifyID) {
			return personLibVec.getAt(i);
		}
	}
	return nullptr;
}

// See notes about passing by pointer.
// The TLDR is that if I update what this is pointed to, IT'S UPDATED ACROSS THE ENTIRE SYSTEM
// (You can also assume that with duplicates, it will return the 1st one it finds. I don't care which.)
cSong* cSnotify::FindSong(std::string title, std::string artist) {
	for (unsigned int i = 0; i < songLibVec.getSize(); i++) {
		if (songLibVec.getAt(i)->artist == artist && songLibVec.getAt(i)->name == title)
			return songLibVec.getAt(i);
	}
	return nullptr;
}

//uses unique id to find song returns a pointer to the song
cSong* cSnotify::FindSong(unsigned int uniqueID) {
	for (unsigned int i = 0; i < songLibVec.getSize(); i++) {
		if (songLibVec.getAt(i)->getUniqueID() == uniqueID)
			return songLibVec.getAt(i);
	}
	return nullptr;
}

// This returns a COPY of the users library, in the form of a regular dynamic array.
bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{

	bool found = false;
	SmartArray<cSong> songVec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			if (personLibVec.getAt(i)->personalSongLibVec.getSize() == 0) {
				sizeOfLibary = 0;
				return false;
			}
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));
				
			}
		}
	}
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

// gets users sorted by title, returns false if there are no users
bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary) {
	bool found = false;
	SmartArray<cSong> songVec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			if (personLibVec.getAt(i)->personalSongLibVec.getSize() == 0) {
				sizeOfLibary = 0;
				return false;
			}
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));

			}
		}
	}
	songVec.quickSortSongByType(0, songVec.getSize() - 1, "name");
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

// takes the personal library of a cPerson and returns it into a dynamic array
bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary) {
	SmartArray<cSong> songVec;
	bool found = false;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			if (personLibVec.getAt(i)->personalSongLibVec.getSize() == 0) {
				sizeOfLibary = 0;
				return false;
			}
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			found = true;
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));
			}
		}
	}
	songVec.quickSortSongByType(0, songVec.getSize() - 1, "artist");
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

//returns the master user list from spotify (smart array) 
bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	if (personLibVec.getSize() == 0) {
		sizeOfUserArray = 0;
		return false;
	}
	SmartArray<cPerson> vec;
	const unsigned int sizeOfArray = personLibVec.getSize() * sizeof(cPerson);
	pAllTheUsers = new cPerson[sizeOfArray];
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		vec.addAtEnd(*personLibVec.getAt(i));
	
	}
	vec.quickSortPersonByType(0, vec.getSize() - 1, "last");
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
	
		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}

// gets a master list of users from snotify lib
bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	if (personLibVec.getSize() == 0) {
		sizeOfUserArray = 0;
		return false;
	}
	SmartArray<cPerson> vec;
	const unsigned int sizeOfArray = personLibVec.getSize() * sizeof(cPerson);
	pAllTheUsers = new cPerson[sizeOfArray];
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		vec.addAtEnd(*personLibVec.getAt(i));

	}
	vec.quickSortPersonByType(0, vec.getSize() - 1, "id");
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {

		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}

//searches snotify lib for any users with the firstname 
bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	SmartArray<cPerson> vec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->first == firstName) {
			vec.addAtEnd(*personLibVec.getAt(i));
		}
	}
	if (vec.getSize() == 0) {
		sizeOfUserArray = 0;
		return false;
	}
	const unsigned int sizeOfArray = vec.getSize() * sizeof(cPerson);
	pAllTheUsers = new cPerson[sizeOfArray];
	vec.quickSortPersonByType(0, vec.getSize() - 1, "last");
	for (unsigned int i = 0; i < vec.getSize(); i++) {
		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}

//search snotify master user list by last person return all users with last name, sorted by first name
bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	SmartArray<cPerson> vec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->last == lastName) {
			vec.addAtEnd(*personLibVec.getAt(i));
		}
	}
	if (vec.getSize() == 0) {
		sizeOfUserArray = 0;
		return false;
	}
	const unsigned int sizeOfArray = vec.getSize() * sizeof(cPerson);
	pAllTheUsers = new cPerson[sizeOfArray];
	vec.quickSortPersonByType(0, vec.getSize() - 1, "first");
	for (unsigned int i = 0; i < vec.getSize(); i++) {
		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}

// searchers master user list for first AND last name, returns all people who have BOTH, sorted by middle name
bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	SmartArray<cPerson> vec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->last == lastName && personLibVec.getAt(i)->last == lastName) {
			vec.addAtEnd(*personLibVec.getAt(i));
		}
	}
	if (vec.getSize() == 0) {
		sizeOfUserArray = 0;
		return false;
	}
	const unsigned int sizeOfArray = vec.getSize() * sizeof(cPerson);
	pAllTheUsers = new cPerson[sizeOfArray];
	vec.quickSortPersonByType(0, vec.getSize() - 1, "middle");
	for (unsigned int i = 0; i < vec.getSize(); i++) {
		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}

