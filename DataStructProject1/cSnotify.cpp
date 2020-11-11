#include "cSnotify.h"

// Operator to sort by title

bool operator < (cSong const& lhs, cSong const& rhs) {
	return lhs.name < rhs.name;
}

bool operator <= (cSong const& lhs, cSong const& rhs) {
	return lhs.name <= rhs.name;
}


bool byArtist(cSong const& lhs, cSong const& rhs) {
	return lhs.artist <= rhs.artist;
}

cSnotify::cSnotify() {

}
cSnotify::~cSnotify() {

}

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
			personLibVec.getAt(i)->personalSongLibVec.addAtEndNoDuplicates(pNewSong);
			personLibVec.getAt(i)->userRatingVec.addAtEnd(0);
			personLibVec.getAt(i)->userSongsPlayedVec.addAtEnd(0);
			return true;
		}
	}
	return false;
}

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


cPerson* cSnotify::FindUserBySIN(unsigned int SIN) {
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->SIN == SIN) {
			return personLibVec.getAt(i);
		}
	}
	return nullptr;
}

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
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));
				
			}
		}
	}
	if (found = false) {
		return false;
	}
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary) {
	bool found = false;
	SmartArray<cSong> songVec;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));

			}
		}
	}
	if (found = false) {
		return false;
	}
	songVec.quickSort(0, songVec.getSize() - 1);
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary) {
	SmartArray<cSong> songVec;
	bool found = false;
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		if (personLibVec.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			const unsigned int sizeOfArray = personLibVec.getAt(i)->personalSongLibVec.getSize() * sizeof(cSong);
			pLibraryArray = new cSong[sizeOfArray];
			found = true;
			for (unsigned int k = 0; k < personLibVec.getAt(i)->personalSongLibVec.getSize(); k++) {
				songVec.addAtEnd(*personLibVec.getAt(i)->personalSongLibVec.getAt(k));
				
			}
		}
	}
	if (found = false) {
		return false;
	}
	songVec.quickSort2(0, songVec.getSize() - 1);
	for (unsigned int i = 0; i < songVec.getSize(); i++) {
		pLibraryArray[i] = songVec.getAt(i);
	}
	sizeOfLibary = songVec.getSize();
	return true;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
	if (personLibVec.getSize() == 0) {
		return false;
	}
	
	SmartArray<cPerson> vec;
	const unsigned int sizeOfArray = personLibVec.getSize() * sizeof(cSong);
	pAllTheUsers = new cPerson[sizeOfArray];
	for (unsigned int i = 0; i < personLibVec.getSize(); i++) {
		vec.addAtEnd(*personLibVec.getAt(i));
		pAllTheUsers[i] = vec.getAt(i);
	}
	sizeOfUserArray = vec.getSize();
	return true;
}