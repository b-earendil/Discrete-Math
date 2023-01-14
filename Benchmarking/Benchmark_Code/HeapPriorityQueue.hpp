// Adapted from Goodrich
#pragma once
#include "VectorCompleteTree.hpp"

template <class NodeType, class C>
class HeapPriorityQueue
{
public:
	int size() const; // number of elements
	bool empty() const; 
	void insert(const NodeType& e);
	const NodeType& min();	
	void removeMin(); 
	void display();
private:
	VectorCompleteTree<NodeType> T;	// vector implementation of heap
	C isLess; // less than comparator

	typedef typename VectorCompleteTree<NodeType>::Position Position; // create alias for Position member of VectorCompleteTree													  
};

template <class NodeType, class C>
int HeapPriorityQueue<NodeType, C>::size() const
{
	return T.size();
}

template <class NodeType, class C>
bool HeapPriorityQueue<NodeType, C>::empty() const
{
	return size() == 0;
}

template <class NodeType, class C>
const NodeType& HeapPriorityQueue<NodeType, C>::min()
{
	return *(T.root());
}

template <class NodeType, class C>
void HeapPriorityQueue<NodeType, C>::insert(const NodeType& e)
{
	T.addLast(e); // add e to heap
	Position v = T.last(); // e's pos
	while (!T.isRoot(v)) { // up-heap bubbling
		Position u = T.parent(v);
		if (!isLess(*v, *u)) break; // if v in order, we're done
		T.swap(v, u); // else swap with parent elem
		v = u;
	}
}

template <class NodeType, class C>
void HeapPriorityQueue<NodeType, C>::removeMin()
{
	if (size() == 1) // only one node
		T.removeLast(); // remove it
	else {
		Position u = T.root(); // root pos
		T.swap(u, T.last()); // swap last with root
		T.removeLast(); 
		while (T.hasLeft(u))
		{ // down-heap bubbling
			Position v = T.left(u);
			if (T.hasRight(u) && isLess(*(T.right(u)), *v))
				v = T.right(u); // v is u's smaller child
			if (isLess(*v, *u)) { // is u out of order
				T.swap(v, u); // then swap
				u = v;
			}
			else break; // else we're done
		}
	}
}

template <class NodeType, class C>
void HeapPriorityQueue<NodeType, C>::display()
{
	T.display();
}
