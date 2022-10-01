
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
	void delete_last(); 
	void delete_first();
	void clear();
	void insert(int index, int data);
	void remove(int index);
	void replace(int index, int data);
	int GetSize() { return Size; };
	bool is_Empty() { return head == nullptr ? true : false; };
	void insert_lst(List &pList);
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
	clear();
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

void List::delete_last()
{
	if (Size > 1)
	{
		Node *temp = tail->pPrev;
		temp->pNext = nullptr;
		delete tail;
		tail = temp;
	}
	else
	{
		head = nullptr;
		tail = nullptr;
	}
	Size--;
}

void List::delete_first()
{
	if (Size > 1)
	{
		Node *temp = head->pNext;
		temp->pPrev = nullptr;
		delete head;
			 
		head = temp;
	}
	else
	{
		head = nullptr;
		tail = nullptr;
	}
	Size--;
}

void List::clear()
{
	while (Size)
	{
		delete_first();
	}
}

void List::insert(int index, int data)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		int counter = 0;
		Node *current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				Node *temp = new Node(data, current->pPrev, current);
				temp->pPrev->pNext = temp;
				current->pPrev = temp;
				Size++;
				break;
			}
			current = current->pNext;
			counter++;
		}
	}
}

void List::remove(int index)
{
	if (index == 0)
	{
		delete_first();
	}
	else if (index == Size - 1)
	{
		delete_last();
	}
	else
	{
		int counter = 0;
		Node *current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				current->pPrev->pNext = current->pNext;
				current->pNext->pPrev = current->pPrev;
				delete current;
				Size--;
				break;
			}
			current = current->pNext;
			counter++;
		}
	}
}

void List::replace(int index, int data)
{
	int counter = 0;
	Node *current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			current->data = data;
			break;
		}
		current = current->pNext;
		counter++;
	}
}

void List::insert_lst(List &pList)
{
	int counter = pList.Size;
	Node *current = new Node;
	current = pList.tail;
	pList.Show();
	while (counter)
	{
		push_front(current->data);
		current = current->pPrev;
		counter--;
	}
	cout << "после вставки: ";
	pList.Show();
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

	lst.Show();
	cout << "Size = " << lst.GetSize() << endl;
	List new_lst;
	List &pNew_lst = new_lst;
	int new_numbersCount;
	cin >> new_numbersCount;

	for (int i = 0; i < new_numbersCount; i++)
	{
		new_lst.push_back(rand() % 10);
	}

	new_lst.Show();
	cout << "Size = " << new_lst.GetSize() << endl;
	lst.insert_lst(new_lst);
	lst.Show();
	cout << "Size = " << lst.GetSize() << endl;
	new_lst.Show();
	cout << "Size = " << new_lst.GetSize() << endl;
}