#ifndef _LINKEDLIST
#define _LINKEDLIST
#include<iostream>
#include "Node.h"
using namespace std;
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	Node<T>* Tail; //Pointer to the tail of the list
	int NumOfNodes;
public:

	Node<T>* gethead() {
		return Head;
	}
	LinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
		NumOfNodes = 0;
	}
	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		Node<T>* p = Head;

		while (p)
		{
			if (p->getNext())
				cout << *p->getItem() << ", ";
			else
				cout << *p->getItem();
			p = p->getNext();
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		NumOfNodes++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		NumOfNodes = 0;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* p = new Node<T>(data);

		if (Head == nullptr) {
			Head = p;
		}
		else {
			Tail->setNext(p);
		}
		Tail = p;
		NumOfNodes++;
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key)
	{
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == Key)
			{
				return true;
			}
			p = p->getNext();
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == value)
			{
				count++;
			}
			p = p->getNext();
		}
		return count;
	}
	//[4] DeleteFirst
	//Deletes the first node in the list
	bool DeleteFirst(T& frstEntry)
	{
		if (Head && Tail) {
			Node<T>* temp = Head;
			frstEntry = Head->getItem();
			Head = Head->getNext();
			if (temp == Tail)
				Tail = nullptr;
			delete temp;
			NumOfNodes--;
			return true;
		}
		else
		{
			return false;
		}
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		if (!Head)
			return;
		if (!Head->getNext())
		{
			delete Head;
			return;
		}
		Node<T>* R = Head;
		while (R->getNext())
		{
			if (!R->getNext()->getNext())
			{
				Node<T>* temp;
				temp = R->getNext();
				delete temp;
				R->setNext(NULL);
				NumOfNodes--;
				return;
			}
			R = R->getNext();
		}
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(T& value)
	{
		if (Head) {
			Node<T>* p = Head;
			Node<T>* temp;
			int c = 0;
			while (p)
			{
				if (p->getItem() == value)
				{
					c++;
					if (p == Head)
					{
						temp = Head;
						Head = Head->getNext();
						NumOfNodes--;
						value = p->getItem();
						return true;
					}
					else if (!p->getNext()->getNext())
					{
						temp = p->getNext();
						p->setNext(NULL);
						NumOfNodes--;
						value = p->getItem();
						return true;
					}
				}
				else if (p->getNext()->getItem() == value)
				{
					temp = p->getNext();
					p->setNext(p->getNext()->getNext());
					NumOfNodes--;
					value = p->getItem();
					return true;
				}
				p = p->getNext();
			}
			if (c == 0)
				return false;
		}
		else
		{
			return false;
		}
	}
	int GetNoOfNodes() const
	{
		return NumOfNodes;
	}
};

#endif