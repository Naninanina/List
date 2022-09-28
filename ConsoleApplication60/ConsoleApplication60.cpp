﻿
#include <iostream>
using namespace std;

class List
{
public:
	List();
	~List();

	void Show();
	void push_back(int data);
	void push_front(int data);
	int GetSize() { return Size; };
	int& operator[](const int index);
private:
	class Node
	{
	public:
		Node *pNext, *pPrev;
		int data;
		Node(int data = int(), Node *pPrev = nullptr, Node *pNext = nullptr)
		{
			this->data = data;
			this->pPrev = pPrev;
			this->pNext = pNext;
		}
	};
	int Size;
	Node *head, *tail;
};

List::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

List::~List()
{
}

void List::Show()
{
	Node *temp = head;

	while (temp != nullptr)
	{
		cout << temp->data << " ";
		temp = temp->pNext;
	}
	cout << endl;
}

void List::push_back(int data)
{
	if (head == nullptr)
	{
		head = tail = new Node(data);
	}
	else
	{
		Node *temp = new Node(data, tail);
		tail->pNext = temp;
		tail = temp;
	}

	Size++;
}

void List::push_front(int data)
{
	if (head == nullptr)
	{
		head = tail = new Node(data);
	}
	else
	{
		Node *temp = new Node(data, nullptr, head);
		head->pPrev = temp;
		head = temp;
	}

	Size++;
}

int & List::operator[](const int index)
{
	int counter = 0;
	Node *current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	List lst;
	int numbersCount;
	cin >> numbersCount;

	for (int i = 0; i < numbersCount; i++)
	{
		lst.push_back(rand() % 10);
	}

	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}
	lst.Show();
	lst.push_front(11);
	lst.Show();
}
