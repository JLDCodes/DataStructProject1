#ifndef _cNode_HG_
#define _cNode_HG_

template <class T>
class cNode
{
public:

	cNode()
	{
		this->pNextNode = nullptr;
		this->pPrevNode = nullptr;
	}
	~cNode()
	{

	}

	T pData;

	cNode* pNextNode;
	cNode* pPrevNode;
};

#endif // !_cNode_HG-