#pragma once
#include "LinkedList.hpp"

template <class NodeType>
class PriorityQueue {
public:
	void insert(NodeType t);
	Node<NodeType>* findMin();
	NodeType& min();
	void removeMin();
	void display();
	int size();
	bool isEmpty();
private:
	LinkedList<NodeType> q;
};

template <class NodeType>
void PriorityQueue<NodeType>::insert(NodeType t)
{
	q.insertFront(t);
}

template <class NodeType>
Node<NodeType>* PriorityQueue<NodeType>::findMin()
{
	Node<NodeType>* ptr = q.head->next;
	int min = ptr->data;
	Node<NodeType>* minPtr = ptr;

	while (ptr) // is not null
	{
		if (ptr->data < min)
		{
			min = ptr->data;
			minPtr = ptr;
		}
		ptr = ptr->next;
	}
	return minPtr;
}

template <class NodeType>
NodeType& PriorityQueue<NodeType>::min()
{
	Node<NodeType>* minPtr = findMin();
	return minPtr->data;
}

template <class NodeType>
void PriorityQueue<NodeType>::removeMin()
{
	NodeType x = q.erase(findMin());
}

//display
template <class NodeType>
void PriorityQueue<NodeType>::display()
{
	q.Display();
}

template <class NodeType>
bool PriorityQueue<NodeType>::isEmpty()
{
	return q.empty();
}

template<class NodeType>
int PriorityQueue<NodeType>::size()
{
	return q.size();
}
