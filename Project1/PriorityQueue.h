/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The Node: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontptr	 backptr
\	 /
\	/
---- NULL ------


Single Node Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <vector>
using namespace std;


template <typename T>
class PriorityQueue :public QueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int NumOfNodes;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~PriorityQueue();
	void printQueue() const;
	int GetNumOFNodes() const;

	//copy constructor
	PriorityQueue(const PriorityQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	NumOfNodes = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry)
{
	NumOfNodes++;
	Node<T>* temp = new Node<T>(newEntry);
	Node<T>* curr = new Node<T>(newEntry);
	Node<T>* pre = new Node<T>(newEntry);
	pre = nullptr;
	temp->setItem(newEntry);

	if (!frontPtr || temp->getItem() >= frontPtr->getItem())
	{
		temp->setNext(frontPtr);
		frontPtr = temp;
	}

	else
	{
		curr = frontPtr;

		while (curr && temp->getItem() <= curr->getItem())
		{
			pre = curr;
			curr = curr->getNext();
		}

		temp->setNext(pre->getNext());
		pre->setNext(temp);
	}
	
	return true;
}
//Node<T>* newNodePtr = new Node<T>(newEntry);
//// Insert the new node
//if (isEmpty())	//special case if this is the first node to insert
//	frontPtr = newNodePtr; // The queue is empty
//else {
//	Node<T>* current = new Node<T>;
//	Node<T>* previous = new Node<T>;
//	current = frontPtr;
//	int numofruns=0;
//	while (current) {
//		numofruns++;
//		if ( current && !current->getNext())
//		{
//			current->setNext(newNodePtr);
//		}
//		if (newNodePtr->getItem()> current->getItem())
//		{
//			if (numofruns==1) {
//				newNodePtr->setNext(frontPtr);
//				frontPtr = newNodePtr;
//			}
//			else {
//				newNodePtr->setNext(current);
//				previous->setNext(newNodePtr);
//			}
//			return true;
//		}
//		if (numofruns==1)
//		{
//			previous = frontPtr;
//		}
//		else {
//			previous = previous->getNext();
//		}
//		current = current->getNext();
//	}
//
//}
//return false;
// end enqueue


 /////////////////////////////////////////////////////////////////////////////////////////////////////////

 /*Function: dequeue
 Removes the front of this queue. That is, removes the item that was added
 earliest.

 Input: None.
 Output: True if the operation is successful; otherwise false.
 */

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	NumOfNodes--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool PriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();
	NumOfNodes++;

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
		NumOfNodes++;
	}
}
template <typename T>
void PriorityQueue<T>::printQueue() const
{
	Node<T>* p = frontPtr;

	while (p)
	{
		if (p->getNext())
			cout << *p->getItem() << ", ";
		else
			cout << *p->getItem();
		p = p->getNext();
	}
}
template <typename T>
int PriorityQueue<T> ::GetNumOFNodes() const {
	return NumOfNodes;
}