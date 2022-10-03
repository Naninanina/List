#include <iostream>
#include <string>

using namespace std;

class List
{
public:
	List();
	~List();

	void autocomplete();
	void Show(string message);
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

void List::Show(string message)
{
	Node *temp = head;

	cout << endl << message;
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
		delete head;
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
		delete head;
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
	while (counter)
	{
		push_front(current->data);
		current = current->pPrev;
		counter--;
	}
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

void print_menu() 
{
	//system("cls");
	cout << "Что вы хотите сделать с этим списком?" << endl;
	cout << "1. Добавить элемент в конец списка" << endl;
	cout << "2. Добавить элемент в начало списка" << endl;
	cout << "3. Удалить последний элемент" << endl;
	cout << "4. Удалить первый элемент" << endl;
	cout << "5. Добавить элемент определенного индекса" << endl;
	cout << "6. Вывести элемент определенного индекса" << endl;
	cout << "7. Удалить элемент определенного индекса" << endl;
	cout << "8. Вывести размер списка" << endl;
	cout << "9. Проверить список на пустоту" << endl;
	cout << "10. Вставить другой список в начало" << endl;
	cout << "11. Выйти" << endl;
	cout << ">";
}

int intValidation()
{
	while (true)
	{
		int val;
		cin >> val;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Вы ввели неверное значение, попробуйте еще раз: ";
		}
		else
		{
			cin.ignore(32767, '\n');
			return val;
		}
	}
}

int checkForExistence(int numOne, int numTwo, string message)
{
	int choice;
	cin >> choice;
	if (choice >= numOne && choice <= numTwo)
	{
		return choice;
	}
	else
	{
		do
		{
			cout << message << endl;
			choice = intValidation();
		} while (!(choice >= numOne && choice <= numTwo));
		return choice;
	}
}

void List::autocomplete()
{
	cout << "Введите, пожалуйста, количество элементов списка: ";
	int numbersCount = checkForExistence(0, 32767, "Мне не нравится это значение. Попробуйте еще раз: ");

	for (int i = 0; i < numbersCount; i++)
	{
		push_back(rand() % 10);
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	List lst, new_lst;
	int data, index, new_numbersCount;

	lst.autocomplete();
	lst.Show("Ваш список: ");

	int choice;

	do {
		print_menu();
		choice = checkForExistence(1, 11, "Вы ввели несуществующий пункт. Повторите попытку: ");

		switch (choice)
		{
		case 1: 
			cout << "Введите элемент, который хотите добавить (int): ";
			data = intValidation();
			lst.push_back(data);
			lst.Show("Измененный список: ");
			break;
		case 2:
			cout << "Введите элемент, который хотите добавить (int): ";
			data = intValidation();
			lst.push_front(data);
			lst.Show("Измененный список: ");
			break;
		case 3:
			lst.delete_last();
			lst.Show("Измененный список: ");
			break;
		case 4:
			lst.delete_first();
			lst.Show("Измененный список: ");
			break;
		case 5:
			cout << "Введите индекс элемента: ";
			index = checkForExistence(0, lst.GetSize() - 1, "Вы ввели несуществующий индекс. Повторите попытку: ");
			cout << "Введите элемент, который хотите добавить (int): ";
			data = intValidation();
			lst.insert(index, data);
			lst.Show("Измененный список: ");
			break;
		case 6:
			cout << "Введите индекс элемента: ";
			index = checkForExistence(0, lst.GetSize() - 1, "Вы ввели несуществующий индекс. Повторите попытку: ");
			cout << "list[" << index << "] = " << lst[index] << endl;
			break;
		case 7:
			cout << "Введите индекс элемента: ";
			index = checkForExistence(0, lst.GetSize() - 1, "Вы ввели несуществующий индекс. Повторите попытку: ");
			lst.remove(index);
			lst.Show("Измененный список: ");
			break;
		case 8:
			cout << "Размер списка = " << lst.GetSize() << endl;
			break;
		case 9:
			if (lst.is_Empty()) cout << "Список пуст." << endl;
			else cout << "Список не пуст." << endl;
			break;
		case 10:
			new_lst.autocomplete();
			lst.Show("Первый список: ");
			new_lst.Show("Второй список: ");
			lst.insert_lst(new_lst);
			lst.Show("Измененный список: ");
			break;
		case 11:
			cout << "Всего доброго!" << endl;
			return 0;
		}
	} while (choice != 11);
}