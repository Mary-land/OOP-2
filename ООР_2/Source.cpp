//#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

struct Node {	int value;	Node* next;};
struct N
{
	int value;	int index;	N* next;
};
class ContainerInterface {
public:
	virtual int Size() const = 0; // возвращает размер контейнера
	virtual bool isEmpty() const = 0; // проверяет пустой ли контейнер
	virtual string toString() const = 0; // строка со всеми элементами
	virtual ~ContainerInterface() {};
};
class PushPopContainerInterface : virtual public ContainerInterface {
public:
	virtual bool push(int value) = 0; // добавить элемент
	virtual int pop() = 0; // забрать элемент
	virtual int peek() const = 0; // узнать элемент
	virtual ~PushPopContainerInterface() {};
};
class Deque : virtual public ContainerInterface {
public:
	virtual bool pushFront(int value) = 0; // добавить в начало
	virtual bool pushBack(int value) = 0; // добавить в конец
	virtual int popFront() = 0; // забрать из начала
	virtual int popBack() = 0; // забрать с конца
	virtual int peekFront() const = 0; // узнать элемент в начале
	virtual int peekBack() const = 0; // узнать элемент с конца
	virtual ~Deque() {};
};
class IndexedContainer : virtual public ContainerInterface {
public:
	virtual int get(int index) const = 0; // узнать элемент по индексу index
	virtual void set(int index, int value) = 0; // задать значение элементу
	virtual ~IndexedContainer() {};
};
class InsertableContainer : virtual public IndexedContainer {
public:
	virtual bool insertAt(int index, int value) = 0; // вставить элемент со сдвигом
	virtual int removeAt(int index) = 0; // убрать элемент со сдвигом
	virtual ~InsertableContainer() {};
};class Stack : public PushPopContainerInterface{private:	Node* first, *current;	int s;public:	Stack(int value)	{		Node *i = new Node();		i->value = value;		i->next = NULL;		first = i;		s = 1;	};	virtual bool push(int value) {
		Node *i = new Node();
		i->value = value;
		i->next = first;
		first = i;
		s++;
		return true;
	};
	virtual int pop() {
		current = first;
		first = first->next;
		--s;
		return current->value;
	};
	virtual int peek() const 	{
		int c;
		if (first == NULL) { c = NULL; }
		else { c = first->value; }
		return c;	};	virtual int Size() const
	{
		return s;
	};
	virtual bool isEmpty() const {
		if (first == NULL) { return true; }
		return false;
	};
	virtual string toString() const {	Node *k = new Node();
	k = first;
	string s;
	while (k != NULL)
	{
	s += " " + to_string(k->value);
	k = k->next;
	}
	return s;	};	~Stack()	{		current = first;		while (first != NULL)		{			current = first->next;			delete first;			first = current;		}		delete[] first;		delete[] current;	};};class Queue : public PushPopContainerInterface{private:	Node* first, *current, *pretail;	int s;public:	Queue(int value)	{		Node *i = new Node();		i->value = value;		i->next = NULL;		first = i;		s=1;	};	virtual bool push(int value) {
		Node *i = new Node();
			i->value = value;
			i->next = NULL;
			if (pretail == NULL)
			{
				first->next = i;
				pretail = first;
			}
			else
			{
				current = pretail->next;
				current->next = i;
				pretail = current;
			}
			s++;
			return true;
	};
	virtual int pop() {
		current = first;
		first = first->next;
		--s;
		return current->value;
	};
	virtual int peek() const 	{
		int c;
		if (first == NULL) { c = NULL; }
		else { c = first->value; }
		return c;	};	virtual int Size() const {
		return s;
	};
	virtual bool isEmpty() const {
		if (first == NULL) { return true; }
		return false;
	};
	virtual string toString() const {		Node *i = new Node();
		i = first;
		string s;
		while (i != NULL)
		{
			s += " " + to_string(i->value);
			i = i->next;
		}
		return s;	};	~Queue() 	{ 		current = first;		while (first != NULL)		{			current = first->next;			delete first;			first = current;		}		delete[] first;		delete[] current;
		delete[] pretail;	};};
class LinkedList : public PushPopContainerInterface, public InsertableContainer
{
private:
	N *first, *current, *tail;
	int s = 0 , count = 0;
public:
	LinkedList(int value)
	{
		N *i = new N();
		i->next = NULL;
		i->index = count;
		count++;
		i->value = value;
		tail = i;
		s = 1;
	}
	virtual bool push(int value) {
		N *i = new N();
		i->index = count;
		i->value = value;
		count++;
		i->next = NULL;
		if (first == NULL)
		{
			tail->next = i;
			first = i;
		}
		else
		{
			first->next = i;
			first = i;
		}
		s++;
		return true;
	};
	virtual int pop() {
		int c;
		current = tail;
		while (current->next!=first)
		{
			current = current->next;
		}
		c = first->value;
		first = current;
		--s;
		return c;
	};
	virtual int peek() const 	{
		int c;
		if (tail == NULL) { c = NULL; }
		else { c = tail->value; }
		return c;	};
	virtual bool insertAt(int index, int value)
	{
		N *v = new N();
		v->index = index;
		v->value = value;
		if (first == NULL)
		{
			if (tail->index >= index)
			{
				v->next = tail;
				first = tail;
				tail = v;
			}
			else 
			{
				tail->next = v;
				first = v;
			}
		}
		else
		{
			N *i = new N();
			current = tail;
			i = NULL;
			while (true)
			{
				if (current->index >= index)
				{
					if (i == NULL)
					{
						v->next = tail;
						if (first == NULL) { first = tail; }
						tail = v;
						break;
					}
					else
					{
						i->next = v;
						v->next = current;
						break;
					}
				}
				if (current->next = NULL)
				{
					current->next = v;
					v->next = NULL;
					first = v;
					break;
				}
				i = current;
				current = current->next;
			}
		}
		s++;
		return true;
	};
	virtual int removeAt(int index)
	{
		N *i = new N();
		int c;
		current = tail;
		i = NULL;
		while (true)
		{
			if (current->index == index)
			{
				if (i == NULL)
				{
					c = tail->value;
					tail = tail->next;
					break;
				}
				else
				{
					i->next = current->next;
					c = current->value;
					--s;
					break;
				}
			}
			if (current->next == NULL)
			{
				c = NULL;
			}
			i = current;
			current = current->next;
		}
		return c;
	};
	virtual int get(int index) const
	{
		N *i = new N();
		int c;
		i = tail;
		while (true)
		{
			if (i->index == index)
			{ 
				c = i->value;
				break;
			}
			if (i->next == NULL)
			{
				c = NULL;
				break;
			}
			i = i->next;
		}
		return c;
	}
	virtual void set(int index, int value)
	{
		current = tail;
		while (current!=NULL)
		{
			if (current->index == index)
			{
				current->value = value;
				break;
			}
			current = current->next;
		}
	}
	virtual int Size() const {
		return s;
	};
	virtual bool isEmpty() const {
		if (tail == NULL) { return true; }
		return false;
	};
	virtual string toString() const {		N *i = new N();
		i = tail;
		string s;
		while (i != NULL)
		{
			s += " " + to_string(i->value);
			i = i->next;
		}
		return s;	};
	~LinkedList()
	{
		current = tail;		while (tail != NULL)		{			current = tail->next;			delete tail;			tail = current;		}		delete[] first;		delete[] current;
		delete[] tail;
	};
};
class StaticArray : public IndexedContainer, public PushPopContainerInterface
{
private:
	N *first, *current, *tail;
	int size, s, count = 0;
public:
	StaticArray(int sz, int value)
	{
		N *i = new N();
		i->next = NULL;
		i->index = count;
		count++;
		i->value = value;
		first = i;
		tail = i;
		size = sz - 1;
		s = 1;
	}
	virtual int get(int index) const
	{
		N *i = new N();
		int c;
		i = first;
		while (true)
		{
			if (i->index == index)
			{
				c = i->value;
				break;
			}
			if (i->next == NULL)
			{
				c = NULL;
				break;
			}
			i = i->next;
		}
		return c;
	};
	virtual void set(int index, int value)
	{
		current = first;
		while (current != NULL)
		{
			if (current->index == index)
			{
				current->value = value;
				break;
			}
			current = current->next;
		}
	};
	virtual bool isEmpty() const
	{
		if (first == NULL) { return true; }
		return false;
	};
	virtual string toString() const
	{
		N *i = new N();
		i = first;
		string k;
		while (i != NULL)
		{
			k += " " + to_string(i->value);
			i = i->next;
		}
		return k;
	};
	virtual bool push(int value) {
		if (size == 0) { return false; }
		else {
			N *i = new N();
			i->value = value;
			i->index = count;
			count++;
			i->next = NULL;
			tail->next = i;
			tail = i;
			size = size - 1;
			s++;
		}
		return true;
	};
	virtual int pop() 
	{
		current = first;
		first = first->next;
		size=size-1;
		s--;
		return current->value;
	};
	virtual int peek() const {
		int c;
		if (first == NULL) { c = NULL; }
		else { c = first->value; }
		return c;	}; 
	virtual int Size() const
	{
		return s;
	};
	~StaticArray()
	{
		current = first;		while (first != NULL)		{			current = first->next;			delete first;			first = current;		}		delete[] first;		delete[] current;
		delete[] tail;
	}
};
class StaticDeque : public Deque
{
private:
	Node *first, *tail, *current;
	int s, size;
public:
	StaticDeque(int sz, int value)
	{
		Node *i = new Node();
		i->next = NULL;
		i->value = value;
		first = i;
		tail = i;
		s = sz - 1;
		size = 1;
	};
	virtual int Size() const
	{
		return size;
	};
	virtual bool isEmpty() const
	{
		if (first == NULL) { return true; }
		return false;
	};
	virtual string toString() const
	{
		Node *i = new Node();
		i = first;
		string s;
		while (i != NULL)
		{
			s += " " + to_string(i->value);
			i = i->next;
		}
		return s;
	};
	virtual bool pushFront(int value)
	{
		if (s == 0) { return false; }
		else
		{
			Node *i = new Node();
			i->value = value;
			i->next = first;
			first = i;
			--s;
			size++;
		}
		return true;
	};
	virtual bool pushBack(int value)
	{
		if (s == 0) { return false; }
		else
		{
			Node *i = new Node();
			i->value = value;
			i->next = NULL;
			tail->next = i;
			tail = i;
			--s;
			size++;
		}
		return true;
	};
	virtual int popFront()
	{
		int c;
		if (first == NULL) { c = NULL; }
		else
		{
			c = first->value;
			first = first->next;
			s++;
			size=size-1;
		}
		return c;
	};
	virtual int popBack()
	{
		int c;
		if (tail == NULL) { c=NULL; }
		else
		{
			c = tail->value;
			if (first == tail)
			{
				first = NULL;
				tail = NULL;
			}
			else
			{
				current = first;
				while (true)
				{
					if (current->next == tail)
					{
						c = tail->value;
						tail = current;
						tail->next = NULL;
						break;
					}
					current = current->next;
				}
			}
			s++;
			size=size-1;
		}
		return c;
	};
	virtual int peekFront() const
	{
		int c;
		if (first == NULL) { c = NULL; }
		else { c = first->value; }
		return c;
	};
	virtual int peekBack() const
	{
		int c;
		if (tail == NULL) { c = NULL; }
		else { c = tail->value; }
		return c;
	};
	~StaticDeque()
	{		current = first;		while ( first != NULL)		{			current = first->next;			delete first;			first = current;		}		delete[] first;		delete[] current;
		delete[] tail;
	};
};

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	ContainerInterface *cont[5];
	cont[0] = new Stack(1);
	cont[1] = new Queue(2);
	cont[2] = new LinkedList(3);
	cont[3] = new StaticArray(10, 4);
	cont[4] = new StaticDeque(20, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << cont[i]->toString() << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		PushPopContainerInterface *p = dynamic_cast<PushPopContainerInterface*>(cont[i]);
		if (p != NULL) {
			p->push(10);
			p->push(20);
			p->push(30);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		cout << cont[i]->toString() << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		PushPopContainerInterface *p = dynamic_cast<PushPopContainerInterface*>(cont[i]);
		if (p != NULL) {
			p->pop();
		}
	}
	for (int i = 0; i < 5; i++)
	{
		cout << cont[i]->toString() << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		Deque *d = dynamic_cast<Deque*>(cont[i]);
		if (d != NULL)
		{
			d->pushFront(1);
			d->pushFront(2);
			d->pushFront(3);
			d->pushFront(4);
			d->pushFront(84);
			d->pushFront(86);
			d->pushFront(18);
			d->pushBack(154);
			d->pushBack(105);
			d->pushBack(115);
			d->pushBack(1005);
			d->pushBack(159);
			while (d->isEmpty() == false)
			{
				cout <<d->popFront() << " ";
			}
		}
	}
	//int n1, n2, k, l, count = 2;
	//bool ind;
	//cout << "Введите размер для StaticArray: ";
	//cin >> n1;
	//StaticArray *a = new StaticArray(n1, 1);
	////while (a->push(count++));
	//while (true)
	//{
	//	ind = a->push(count);
	//	if (ind == false) { break; }
	//	else { count++; }
	//}
	//cout << "Содержимое StaticArray:" << a->toString() << endl;
	//cout << "Введите индекс искомого элемента: ";
	//cin >> k;
	//cout << "Значение элемента с искомым индексом: " << a->get(k) << endl;
	//cout << "Введите индекс элемента, значение которого хотите изменить: ";
	//cin >> k;
	//cout << "Введите новое значение: ";
	//cin >> l;
	//a->set(k, l);
	//cout << "Содержимое StaticArray:" << a->toString() << endl;
	//cout << "Введите количество элементов, которые хотите изъять: ";
	//cin >> k;
	//while (k != 0)
	//{
	//	a->pop();
	//	--k;
	//}
	//cout << "Проверим, пуст ли StaticArray: " << a->isEmpty() << endl;
	//cout << "Первый элемент StaticArray: " << a->peek() << endl;
	//cout << "Содержимое StaticArray:" << a->toString() << endl;
	//cout << "Размер StaticArray: " << a->Size() << endl;
	//cout << endl << "Введите размер для StaticDeque: ";
	//cin >> n2;
	//StaticDeque *d = new StaticDeque(n2, count);
	//count++;
	//cout << "Сколько элементов добавить в начало для StaticDeque: ";
	//cin >> k;
	//while (true)
	//{
	//	if (k != 0)
	//	{
	//		ind = d->pushFront(count);
	//		--k;
	//		if (ind == false) { break; }
	//		else { count++; }
	//	}
	//	else
	//	{
	//		ind = d->pushBack(count);
	//		if (ind == false) { break; }
	//		else { count++; }
	//	}
	//}
	//cout << "Содержимое StaticDeque:" << d->toString() << endl;
	//cout << "Введите количество элементов, которые хотите изъять из начала: ";
	//cin >> k;
	//while (k != 0)
	//{
	//	d->popFront();
	//	--k;
	//}
	//cout << "Введите количество элементов, которые хотите изъять с конца: ";
	//cin >> k;
	//while (k != 0)
	//{
	//	d->popBack();
	//	--k;
	//}
	//cout << "Проверим, пуст ли StaticDeque:: " << d->isEmpty() << endl;
	//cout << "Первый элемент: " << d->peekFront() << endl;
	//cout << "Последний элемент: " << d->peekBack() << endl;
	//cout << endl << "Содержимое StaticDeque:" << d->toString() << endl;
	//cout << "Размер StaticDeque: " << d->Size() << endl;
	//
	system("pause");


	return 0;
}