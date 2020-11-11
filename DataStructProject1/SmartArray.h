
#pragma once


template <class T> class SmartArray
{
public:
	using value_type = T; //type of data in SmartArray
	using value_type_pointer = value_type*;
	using value_type_reference = value_type&;
	using value_type_const_reference = const value_type&;
	using size_type = size_t;
	value_type* pArray_;

private:
	unsigned int capacity_;
	unsigned int size_;
	
	//double in size
	void grow() {
		capacity_ *= 2;
		value_type* new_array = new value_type[capacity_];
		for (unsigned int i = 0; i < this->size_; i++)
			new_array[i] = pArray_[i];
		delete[] pArray_;
		pArray_ = new_array;
	}

public:

	void removeFromVec(unsigned int index) {
		value_type* new_array = new value_type[capacity_];
		int count = 0;
		for (unsigned int i = 0; i < size_; i++) {
			if (i != index) {
				new_array[count++] = pArray_[i];	
			}
		}
		delete[] pArray_;
		pArray_ = new_array;
		size_ = count;
	}

	//set start value 
	SmartArray() {
		pArray_ = new value_type[10];
		capacity_ = 10;
		size_ = 0;
	}

	~SmartArray() {
		//delete[] pArray_;
	}

	void addAtEnd(value_type to_insert) {
		if (size_ == capacity_)
			grow();
		pArray_[size_++] = to_insert;
	}

	void update(unsigned int index, value_type to_update) {
		pArray_[index] = to_update;
	}

	bool  addAtEndNoDuplicates(value_type to_insert) {
		if (size_ == capacity_)
			grow();
		bool duplicate = false;
		for (unsigned int i = 0; i < size_; i++) {
			if (pArray_[i] == to_insert) {
				duplicate = true;
			}
		}
		if (duplicate == false) {
			pArray_[size_++] = to_insert;
			return true;
		}
		return false;
	}



	value_type getAt(int index) {
		return *(pArray_ + index);
	}

	unsigned int getSize(void) {
		return this->size_;
	}

	void clear() {
		delete[] pArray_;
		pArray_ = new value_type[10];
		capacity_ = 10;
		size_ = 0;
	}

	bool isEmpty() {
		if (size_ == 0) {
			return true;
		}
		return false;
	}


	void quickSortByType(int low, int high, std::string type)
	{
		if (low < high)
		{
			int pi = partitionByType(low, high, type);
			quickSortByType(low, pi - 1, type);
			quickSortByType(pi + 1, high, type);
		}
	}


	int partitionByType(int low, int high, std::string type)
	{
		value_type pivot = this->getAt(high);
		int i = (low - 1);
		bool swap = false;
		for (int j = low; j <= high - 1; j++)
		{

			if (type == "artist") {
				if ((this->getAt(j).artist <= pivot.artist)) {
					swap = true;
				}
			}
			if (type == "name") {
				if ((this->getAt(j).name <= pivot.name)) {
					swap = true;
				}
			}
			if (swap==true)
			{
				i++;
				//swap 
				value_type hold = pArray_[i];
				pArray_[i] = pArray_[j];
				pArray_[j] = hold;
			}
			swap = false;
		}
		//swap
		value_type hold2 = this->getAt(i + 1);
		pArray_[i + 1] = pArray_[high];
		pArray_[high] = hold2;
		return (i + 1);
	}

	void quickSortPersonByType(int low, int high, std::string type)
	{
		if (low < high)
		{
			int pi = partitionPersonByType(low, high, type);
			quickSortPersonByType(low, pi - 1, type);
			quickSortPersonByType(pi + 1, high, type);
		}
	}


	int partitionPersonByType(int low, int high, std::string type)
	{
		value_type pivot = this->getAt(high);
		int i = (low - 1);
		bool swap = false;
		for (int j = low; j <= high - 1; j++)
		{

			if (type == "first") {
				if ((this->getAt(j).first <= pivot.first)) {
					swap = true;
				}
			}
			if (type == "middle") {
				if ((this->getAt(j).middle <= pivot.middle)) {
					swap = true;
				}
			}
			if (type == "last") {
				if ((this->getAt(j).last <= pivot.last)) {
					swap = true;
				}
			}
			if (type == "sin") {
				if ((this->getAt(j).SIN <= pivot.SIN)) {
					swap = true;
				}
			}
			if (type == "id") {
				if ((this->getAt(j).m_Snotify_UniqueUserID <= pivot.m_Snotify_UniqueUserID)) {
					swap = true;
				}
			}
			if (swap == true)
			{
				i++;
				//swap 
				value_type hold = pArray_[i];
				pArray_[i] = pArray_[j];
				pArray_[j] = hold;
			}
			swap = false;
		}
		//swap
		value_type hold2 = this->getAt(i + 1);
		pArray_[i + 1] = pArray_[high];
		pArray_[high] = hold2;
		return (i + 1);
	}


};

