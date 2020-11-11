#ifndef _cLinkedList_HG_
#define _cLinkedList_HG_

#include "cNode.h"

template <class T>
class cLinkedList
{
public:
	cLinkedList()
	{
		this->firstNodePtr = NULL;
		this->CurrentNodePtr = NULL;
		this->lastNodePtr = NULL;
		this->size_ = 0;
	}

	~cLinkedList()
	{
		//delete all the nodes
		clear();
	}

	//insert a new node value at the current location 
	//It inserts before the current location! 
	bool insert(T objectToInsert)
	{
		//creating new node
		cNode<T>* newNode = new cNode<T>;

		//storing object into node 
		newNode->pData = objectToInsert;

		// If there is no nodes 
		if (this->CurrentNodePtr == NULL)
		{
			this->CurrentNodePtr = newNode;
			this->firstNodePtr = newNode;
			size_++;
			return true;
		}
		//is this the last node?
		if (this->CurrentNodePtr->pNextNode == NULL)
		{
			this->CurrentNodePtr->pNextNode = newNode;
			newNode->pPrevNode = this->CurrentNodePtr;
			this->lastNodePtr = newNode;
			this->CurrentNodePtr = newNode;
			size_++;
			return true;
		}
		//is this going to inserted in the begining of the list?
		if (this->CurrentNodePtr->pPrevNode == NULL)
		{
			//update the links for the old first node
			newNode->pNextNode = this->CurrentNodePtr;
			this->CurrentNodePtr->pPrevNode = newNode;
			//update the info 
			this->CurrentNodePtr = newNode;
			this->firstNodePtr = newNode;
			size_++;
			return true;
		}

		//if not the first or the last 
		if (this->CurrentNodePtr->pNextNode != NULL && this->CurrentNodePtr->pPrevNode != NULL)
		{
			//right-hand side updating links
			newNode->pNextNode = this->CurrentNodePtr->pNextNode;
			this->CurrentNodePtr->pNextNode->pPrevNode = newNode;
			newNode->pPrevNode = this->CurrentNodePtr;

			//left-hand side updating links 
			//establishing link to old node that is currently stored as currentnode
			newNode->pPrevNode = this->CurrentNodePtr;
			//establishing the link from the old node (which is currentnode) to new current node
			this->CurrentNodePtr->pNextNode = newNode;

			//assign current node to new node
			this->CurrentNodePtr = newNode;
			size_++;
			return true;
		}


		//nothing happened. 
		return false;
	}
	//deleted the node value at current location 
	bool deleteNode()
	{
		// Is there a node? 
		if (this->CurrentNodePtr == NULL)
		{
			return false;
		}
		//is this first node?
		if (this->CurrentNodePtr->pPrevNode == NULL)
		{

			if (size_ > 1)
			{
				//delete the link 
				this->CurrentNodePtr->pNextNode->pPrevNode = NULL;
				//update the new first node 
				this->CurrentNodePtr->pNextNode = this->firstNodePtr;
			}

			//assign the new currentNode to the nextnode (first node)
			this->CurrentNodePtr = this->firstNodePtr;

			//delete the node
			delete this->CurrentNodePtr;
			size_--;
			return true;
		}
		//is this the last node? 
		if (this->CurrentNodePtr->pNextNode == NULL)
		{
			//delete the link  
			this->CurrentNodePtr->pPrevNode->pNextNode = NULL;
			//update the new last node
			this->CurrentNodePtr->pPrevNode = this->lastNodePtr;

			//assign the new currentNode to the lastnode
			this->CurrentNodePtr = this->lastNodePtr;

			//delete the node
			delete this->CurrentNodePtr;
			size_--;
			return true;
		}

		if (this->CurrentNodePtr->pNextNode != NULL && this->CurrentNodePtr->pPrevNode != NULL)
		{
			//destroy the links (destory wants pointing to it)
			this->CurrentNodePtr->pPrevNode->pNextNode = NULL;
			this->CurrentNodePtr->pNextNode->pPrevNode = NULL;

			//link up the nodes before and after the current node that will be deleted 
			this->CurrentNodePtr->pPrevNode->pNextNode = this->CurrentNodePtr->pNextNode;
			this->CurrentNodePtr->pNextNode->pPrevNode = this->CurrentNodePtr->pPrevNode;

			//create new node to store node
			cNode<T>* toDelete = new cNode<T>;
			//store the location of the next node 
			toDelete = this->CurrentNodePtr;

			//assign the new currentNode to the prevnode
			this->CurrentNodePtr = this->CurrentNodePtr->pPrevNode;

			//delete the node 
			delete toDelete;
			size_--;
			return true;
		}


		return false;

	}
	//move to the next node value (if present)
	bool MoveNext()
	{
		//does the current node point to anything
		if (this->CurrentNodePtr->pNextNode == NULL)
		{
			//return false and not move 
			return false;
		}
		//There is data and I'm pointing to a valid node 
		this->CurrentNodePtr = this->CurrentNodePtr->pNextNode;
		return true;
	}
	//move to the preivous node value (if present)
	bool MovePrevious()
	{
		//does the current node point to anything
		if (this->CurrentNodePtr->pPrevNode == NULL)
		{
			//return false and not move 
			return false;
		}
		//There is data and I'm pointing to a valid node 
		this->CurrentNodePtr = this->CurrentNodePtr->pPrevNode;
		return true;
	}
	//move to the 1st node(the "head") 
	void moveToFirst()
	{
		this->CurrentNodePtr = this->firstNodePtr;
		return;
	}
	//move to the last node (the "tail")
	void moveToLast()
	{
		this->CurrentNodePtr = this->lastNodePtr;
		return;
	}
	//get the value at the current location
	T getCurrent()
	{
		return this->CurrentNodePtr->pData;
	}
	//is the list empty 
	bool isEmpty()
	{
		if (this->firstNodePtr == NULL)
		{
			return true;
		}
		return false;
	}
	//clear all nodes data from the list 
	bool clear()
	{

		//it is empty already?
		if (this->CurrentNodePtr == NULL)
		{
			return false;
		}
		//if not then lets clear this list 
		moveToFirst();
		cNode<T>* next = new cNode<T>;

		while (this->CurrentNodePtr->pNextNode != NULL)
		{
			//store the location of the next node 
			next = this->CurrentNodePtr->pNextNode;
			//free the current node we at
			delete this->CurrentNodePtr;
			//move current node to the next node 
			this->CurrentNodePtr = next;
		}
		//clear the last node 
		delete this->lastNodePtr;

		this->firstNodePtr = NULL;
		this->CurrentNodePtr = NULL;
		this->lastNodePtr = NULL;

		return true;
	}

	cNode<T>* update_CurrentNode()
	{
		return CurrentNodePtr;
	}

	T getNodeInfoAt(unsigned int position)
	{
		//just return the initial value 
		if (position >= this->size_)
		{
			return this->CurrentNodePtr->pData;
		}
		this->moveToFirst();
		if (position == 0)
		{
			return this->CurrentNodePtr->pData;
		}
		for (unsigned int i = 0; i < position; i++)
		{
			this->MoveNext();
		}

		return this->CurrentNodePtr->pData;
	}

	unsigned int getSize()
	{
		return this->size_;
	}

private:

	cNode<T>* firstNodePtr;
	cNode<T>* lastNodePtr;
	cNode<T>* CurrentNodePtr;
	unsigned int size_;
};

#endif