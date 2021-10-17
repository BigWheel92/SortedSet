#pragma once
#include <iostream>

class IndexOutOfRange : std::exception
{
};

template <typename T>
struct Node
{
	T data;
	Node* next;
};

template <typename T>
class SortedSet
{
private:
	Node<T>* head;
	Node<T>* tail;
	int totalElements = 0;

private:
	void insertAtHead(T const&);
	void insertAtTail(T const&);
	void deleteFromHead();
	void deleteAfter(Node<T>*);
	void appendList(Node<T>*);
	void insertAfter(Node<T>*, T const&);

public:
	SortedSet();
	void insert(T const&);
	void delete_(int const&);
	void union_(SortedSet<T> const&);
	void intersection(SortedSet<T> const&);
	void deleteAll();
	bool isEmpty() const;
	void print()const;
	~SortedSet();
};

template <typename T>
SortedSet<T>::SortedSet()
{
	this->head = this->tail = nullptr;
	this->totalElements = 0;
}

template <typename T>
void SortedSet<T>::deleteAll()
{
	if (!this->isEmpty())
	{
		while (this->head)
		{
			Node<T>* delNode = this->head;
			this->head = this->head->next;
			delete delNode;
		}
		this->totalElements = 0;
	}
}

template <typename T>
void SortedSet<T>::union_(SortedSet<T> const& otherList)
{
	if (otherList.isEmpty())
		return;
	
	if (this->isEmpty())
		appendList(otherList.head);

	else
	{
		Node<T>* prev = nullptr;
		Node<T>* curr1 = this->head;
		Node<T>* curr2 = otherList.head;

		while (curr1 != nullptr && curr2 != nullptr)
		{
			if (curr1->data == curr2->data)
			{
				prev = curr1;
				curr1 = curr1->next;
				curr2 = curr2->next;
			}
			else if (curr1->data > curr2->data)
			{
				if (prev == nullptr)
				{
					this->insertAtHead(curr2->data);
					prev = this->head;
				}
				else
				{
					this->insertAfter(prev, curr2->data);
					prev = prev->next;
				}

				curr2 = curr2->next;
			}
			else // curr1->next->data < curr2->next->data
			{
				prev = curr1;
				curr1 = curr1->next;
			}
		}

		//if this list has ended but the other list has not ended
		if (curr2 != nullptr)
			this->appendList(curr2);
	}
}

template <typename T>
void SortedSet<T>::intersection(SortedSet<T> const& otherList)
{
	if (this->isEmpty())
		return;

	if (otherList.isEmpty())
	{
		this->deleteAll();
		return;
	}

	Node<T>* prev = nullptr;
	Node<T>* curr1 = this->head;
	Node<T>* curr2 = otherList.head;

	while (curr1 != nullptr && curr2 != nullptr)
	{
		if (curr1->data == curr2->data)
		{
			prev = curr1;
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		else if (curr1->data < curr2->data)
		{
			curr1 = curr1->next;
			if (prev == nullptr)
				this->deleteFromHead();
			else
				this->deleteAfter(prev);
		}
		else //curr1->data > curr2->data
		{
			curr2 = curr2->next;
		}
	}

	if (prev != nullptr) 
	{
		//if the other list has ended but this list has not ended.
		while (prev->next != nullptr)
			deleteAfter(prev);
	}
}

template <typename T>
void SortedSet<T>::insertAfter(Node<T>* curr, T const& data)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->next = curr->next;
	curr->next = newNode;

	if (newNode->next == nullptr)
		this->tail = newNode;

	this->totalElements++;
}

template <typename T>
void SortedSet<T>::insert(T const & data)
{
	//checking whether the data needs to be inserted at head.
	if (this->isEmpty() || this->head->data > data)
		this->insertAtHead(data);

		//checking whether the data needs to be inserted at tail.
	else if (this->tail->data < data)
		this->insertAtTail(data);

	else
	{
		Node<T>* curr = this->head;
		while (curr->data != data && curr->next != nullptr)
		{
			if (curr->next->data > data)
			{
				//we will insert between curr and curr->next
				Node<T>* newNode = new Node<T>;
				newNode->data = data;
				newNode->next = curr->next;
				curr->next = newNode;
				this->totalElements++;
				break;
			}

			curr = curr->next;
		}
	}
}

template <typename T>
void SortedSet<T>::insertAtHead(T const& data)
{
	if (isEmpty())
	{
		this->head = this->tail = new Node<T>();
		this->head->data = data;
		this->head->next = nullptr;
		this->totalElements++;
	
	}
	else
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		newNode->next = this->head;
		this->head = newNode;
		this->totalElements++;
	}
}

template <typename T>
void SortedSet<T>::insertAtTail(T const& data)
{
	if (this->isEmpty()) //if list is empty.
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		newNode->next = nullptr;
		this->head = this->tail = newNode;
		this->totalElements++;
	}
	else
	{
		this->tail->next = new Node<T>;
		this->tail->next->data = data;
		this->tail->next->next = nullptr;
		this->tail = this->tail->next;
		this->totalElements++;
	}
}

template <typename T>
void SortedSet<T>::delete_(int const & index)
{

	if (index<0 || index > this->totalElements-1)
		throw new IndexOutOfRange; //index number is out of range.

	else if (index==0)
		this->deleteFromHead();
	else
	{
		Node<T>* curr = this->head;
		int counter = 0;
		while (counter != index-1)
		{
			curr = curr->next;
			counter++;
		}

		deleteAfter(curr);
	}
}

template <typename T>
bool SortedSet<T>::isEmpty() const
{
	return this->head == nullptr;
}

template <typename T>
void SortedSet<T>::deleteFromHead()
{
	if (this->isEmpty())
		return;

	//if there is only one element in the set
	if (this->head == this->tail)
	{
		delete this->head;
		this->head = this->tail = nullptr;
		this->totalElements--;

	}
	else
	{

		Node<T>* delNode = this->head;
		this->head = this->head->next;
		delete delNode;
		this->totalElements--;
	}
}

template <typename T>
void SortedSet<T>::print() const
{
	Node<T>* curr = this->head;
	while (curr)
	{
		std::cout << curr->data << std::endl;
		curr = curr->next;
	}
}

template <typename T>
void SortedSet<T>::deleteAfter(Node<T>* curr)
{
	Node<T>* delNode = curr->next;
	curr->next = curr->next->next;

	//if the node to be deleted is the tail node, then update tail node.
	if (curr->next == nullptr)
		this->tail = curr;

	delete delNode;
	this->totalElements--;
}

template<typename T>
void SortedSet<T>::appendList(Node<T>* otherListNode)
{
	while (otherListNode != nullptr)
	{
		this->insertAtTail(otherListNode->data);
		otherListNode = otherListNode->next;
	}
}

template <typename T>
SortedSet<T>::~SortedSet()
{
	deleteAll();
}