
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

	bool  addAtEndNoDuplicates(value_type to_insert) {
		if (size_ == capacity_)
			grow();
		bool duplicate = false;
		for (int i = 0; i < size_; i++) {
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

	int partition(int low, int high)
	{
		value_type pivot = this->getAt(high);
		int i = (low - 1);
		for (int j = low; j <= high - 1; j++)
		{
			if (this->getAt(j) <= pivot)
			{
				i++;
				//swap 
				value_type hold = pArray_[i];
				pArray_[i] = pArray_[j];
				pArray_[j] = hold;
			}
		}
		//swap
		value_type hold2 = this->getAt(i + 1);
		pArray_[i + 1] = pArray_[high];
		pArray_[high] = hold2;
		return (i + 1);
	}

	/* low  --> Starting index,  high  --> Ending index */
	void quickSort(int low, int high)
	{
		if (low < high)
		{
			int pi = partition(low, high);
			quickSort(low, pi - 1);
			quickSort(pi + 1, high);
		}
	}

};

