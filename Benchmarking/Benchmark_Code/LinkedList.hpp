#pragma once
#include <iostream> // cin, cout

template <class NodeType>
struct Node {
	NodeType data = NodeType();
	Node<NodeType>* next = nullptr;
	Node<NodeType>* prev = nullptr;
};

template <class NodeType>
class LinkedList {
public:
	LinkedList(); // copy ctor 
	LinkedList<NodeType>(const LinkedList<NodeType>& that); // copy assignment
	LinkedList<NodeType>& operator=(const LinkedList<NodeType>& that);
	virtual ~LinkedList(); // dtor

	void Display();
	int size(); 
	bool empty(); 
	void insertFront(const NodeType& item);
	NodeType removeFront();
	void insertBack(const NodeType& item);
	NodeType removeBack();
	NodeType erase(Node<NodeType>* elem);
	NodeType getHead() { return head->next->data; };
	NodeType getTail() { return tail->data; };
	void removeDup();
	void clear(); // remove all nodes

	template <class NodeType> // may not be needed
	friend class PriorityQueue;
private:
	Node<NodeType>* head = nullptr;
	Node<NodeType>* tail = nullptr;
	int n = 0; // node counter
};

// ctor
template <class NodeType>
LinkedList<NodeType>::LinkedList()
{
	head = new Node<NodeType>;
	head->prev = head->next = nullptr;
	tail = head;
}

// copy ctor
template <class NodeType>
LinkedList<NodeType>::LinkedList(const LinkedList<NodeType>& that) 
{
	if (that.head->next == nullptr)
	{
		head = new Node<NodeType>;
		head->prev = head->next = nullptr;
		tail = head;
	}
	else
	{
		head = new Node<NodeType>;
		head->prev = nullptr;
		Node<NodeType>* curr = head;
		Node<NodeType>* thatHead = that.head; // may not be necessary, next line only could work
		Node<NodeType>* thatObj = thatHead;
		while (thatObj->next != nullptr)
		{
			curr->next = new Node<NodeType>;
			curr->next->data = thatObj->next->data;
			thatObj = thatObj->next;
			curr = curr->next;
			tail = curr;
		}
	}
}

// copy assignment
template <class NodeType>
LinkedList<NodeType>& LinkedList<NodeType>::operator=(const LinkedList<NodeType>& that)
{
	if (this == &that) // check for self-assignment
		return *this;
	if (head->next != nullptr) // check if list already has values
		this->clear();		   // if so, clear them
	Node<NodeType>* thatObj = that.head;
	Node<NodeType>* curr = head;
	while (thatObj->next != nullptr)
	{
		curr->next = new Node<NodeType>;
		curr->next->data = thatObj->next->data;
		thatObj = thatObj->next;
		curr = curr->next;
		tail = curr;
	}
	return *this;
}


// dtor
template <class NodeType>
LinkedList<NodeType>::~LinkedList()
{
	Node<NodeType>* p = head;
	while (head->next)
	{
		head = head->next;
		delete p;
		p = head;
	}
	delete head;
}

// display
template <class NodeType>
void LinkedList<NodeType>::Display()
{
	Node<NodeType>* p = head; // use p so head won't fail condition in dtor
	while (p->next != nullptr)      // head->next would have set head to nullptr
	{
		std::cout << p->next->data << " ";
		p = p->next;
	}
}

// size
template <class NodeType>
int LinkedList<NodeType>::size()
{
	return n;
}

// empty
template <class NodeType>
bool LinkedList<NodeType>::empty()
{
	return head == tail;
}

// insert_front
template <class NodeType>
void LinkedList<NodeType>::insertFront(const NodeType& item)
{
	Node<NodeType>* t = new Node<NodeType>;
	t->data = item;
	if (head->next == nullptr) // if list does not contain nodes
	{
		t->next = nullptr;
		t->prev = head;
		head->next = t;
		tail = t;
	}
	else // if list contains nodes
	{
		t->prev = head;
		head->next->prev = t;
		t->next = head->next;
		head->next = t;
	}
	n++;
}

// insert_back
template <class NodeType>
void LinkedList<NodeType>::insertBack(const NodeType& item)
{
	Node<NodeType>* t = new Node<NodeType>;
	t->data = item;
	if (head->next == nullptr) // if list does not contain nodes
	{
		t->next = nullptr;
		t->prev = head;
		head->next = t;
		tail = t;
	}
	else // if list contains nodes
	{
		t->next = nullptr;
		tail->next = t;
		t->prev = tail;
		tail = t;
	}
	n++;
}

// remove_front
template <class NodeType>
NodeType LinkedList<NodeType>::removeFront()
{
	NodeType x;
	Node<NodeType>* p = head;
	if (head->next != nullptr) // if list contains nodes
	{
		p = p->next;
		x = p->data;
		if (p->next) // if p not at tail
		{
			p->next->prev = p->prev;
			p->prev->next = p->next;
			delete(p);
			n--;
		}
		else // if p at tail
		{
			p->prev->next = nullptr;
			tail = head;
			delete(p);
			n--;
		}
		return x;
	}
	else
	{
		throw std::exception("Error: Empty List");
	}
}

// remove_back
template <class NodeType>
NodeType LinkedList<NodeType>::removeBack()
{
	if (head->next != nullptr) //if list contain nodes
	{
		NodeType x;
		Node<NodeType>* p = tail;
		x = tail->data;
		tail = tail->prev;
		tail->next = nullptr;
		delete(p);
		n--;
		return x;
	}
	else // if list does not contain nodes
	{
		throw std::exception("Error: Empty List");
	}
}

//erase
template <class NodeType>
NodeType LinkedList<NodeType>::erase(Node<NodeType>* minPtr) // used with PriorityQueue to delete min elem at any position
{
	NodeType x = minPtr->data;;
	if (head->next != nullptr) // if list contains nodes
	{
		if (minPtr->next) // if min_ptr not at tail
		{
			minPtr->next->prev = minPtr->prev;
			minPtr->prev->next = minPtr->next;
			delete(minPtr);
			n--;
		}
		else // if min_ptr at tail
		{
			minPtr->prev->next = nullptr;
			tail = minPtr->prev;
			delete(minPtr);
			n--;
		}
		return x;
	}
	else
	{
		throw std::exception("Error: Empty List");
	}
}


//clear
template <class NodeType>
void LinkedList<NodeType>::clear() // does not delete head, only the data nodes
{
	Node<NodeType>* p = head;
	if (head->next != nullptr) { // if list contains nodes
		while (head->next != nullptr)
		{
			head = head->next;
			head->prev = nullptr;
			delete(p);
			n--;
			p = head;
		}
	}
	else
	{
		throw std::exception("Error: Empty List");
	}
}

// remove_dup
template <class NodeType>
void LinkedList<NodeType>::removeDup()
{
	Node<NodeType>* ptr1 = this->head->next;
	Node<NodeType>* ptr2, * dup;

	// access each element
	while (ptr1 != nullptr && ptr1->next != nullptr)
	{
		ptr2 = ptr1;

		// compare the selected element with the rest
		while (ptr2->next != nullptr)
		{
			// if dup, delete
			if (ptr1->data == ptr2->next->data)
			{
				dup = ptr2->next;
				ptr2->next->prev = ptr2;
				tail = ptr2->next = ptr2->next->next;
				delete(dup);
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}


