#ifndef PRI_LINKED_QUEUE_
#define PRI_LINKED_QUEUE_

#include "Node.h"
using namespace std;

template <typename T, typename G>
class Pair
{
public:
	T first;
	G second;
};

template <typename T>
class PriorityLinkedQueue
{
private:
	Node<Pair<T, int>>* frontPtr;
	Node<Pair<T, int>>* backPtr;
public:
	PriorityLinkedQueue();
	bool isEmpty() const;
	bool enqueue(const Pair<T, int>& newEntry);
	bool dequeue(Pair<T, int>& frntEntry);
	bool peek(Pair<T, int>& frntEntry)  const;
	void clear();
	~PriorityLinkedQueue();

	//copy constructor
	PriorityLinkedQueue(const PriorityLinkedQueue<T>& LQ);
};

template <typename T>
PriorityLinkedQueue<T>::PriorityLinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

template <typename T>
bool PriorityLinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
bool PriorityLinkedQueue<T>::enqueue(const Pair<T, int>& newEntry)
{
	Node<Pair<T, int>>* newNodePtr = new Node<Pair<T, int>>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = backPtr = newNodePtr; // The queue is empty
	else if (newNodePtr->getItem().second > frontPtr->getItem().second)
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else if (newNodePtr->getItem().second == frontPtr->getItem().second)
	{
		newNodePtr->setNext(frontPtr->getNext());
		frontPtr->setNext(newNodePtr);
	}
	else
	{
		Node<Pair<T, int>>* Prev = frontPtr, * P = frontPtr->getNext();
		while (P && newNodePtr->getItem().second < P->getItem().second && newNodePtr->getItem().second != P->getItem().second)
		{
			Prev = P;
			P = P->getNext();
		}
		if (!P)
		{
			Prev->setNext(newNodePtr);
			backPtr = newNodePtr;
		}
		else if (newNodePtr->getItem().second > P->getItem().second)
		{
			newNodePtr->setNext(P);
			Prev->setNext(newNodePtr);
		}
		else if (newNodePtr->getItem().second == P->getItem().second)
		{
			newNodePtr->setNext(P->getNext());
			P->setNext(newNodePtr);
		}
	}
	while (backPtr->getNext())
		backPtr = backPtr->getNext();
	return true;
}

template <typename T>
bool PriorityLinkedQueue<T>::dequeue(Pair<T, int>& frntEntry)
{
	if (isEmpty())
		return false;

	Node<Pair<T, int>>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	delete nodeToDeletePtr;
	return true;
}

template <typename T>
bool PriorityLinkedQueue<T>::peek(Pair<T, int>& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

template <typename T>
void PriorityLinkedQueue<T>::clear()
{
	Pair<T, int> temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template <typename T>
PriorityLinkedQueue<T>::~PriorityLinkedQueue()
{
	clear();
}

template <typename T>
PriorityLinkedQueue<T>::PriorityLinkedQueue(const PriorityLinkedQueue<T>& LQ)
{
	Node<Pair<T, int>>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}
	//insert the first node
	Node<Pair<T, int>>* ptr = new Node<Pair<T, int>>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<Pair<T, int>>* ptr = new Node<Pair<T, int>>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif

