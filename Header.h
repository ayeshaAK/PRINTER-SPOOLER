#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

struct Document
{
public:
	string doc_id;
	string user_id;
	int NoOfPages;
	Document* next;
	Document();
	Document(string, string, int);
	Document(const Document& obj);
	const Document& operator=(const Document& obj);
	~Document();
};

class Queue
{
public:
	int size;
	Document* cur;
	Document* head;
	Document* tail;
	Queue();
	bool queueEmpty() const;
	const Queue& operator=(const Queue& obj);
	void clear();
	void display()const;
	int getLength();
	void Enqueue(string, string, int);
	Document* Dequeue();
	~Queue();
};

/************************************* class Document node  ***************************************/
Document::Document()
{
	doc_id = "";
	NoOfPages = 0;
	next = NULL;
}
Document::Document(string name, string username, int pn) {
	this->doc_id = name;
	this->user_id = username;
	this->NoOfPages = pn;
	this->next = NULL;
}
Document::Document(const Document &obj) {
	
	*this = obj;
}
const Document& Document::operator=(const Document& obj) {

	if (this != &obj)
	{
		doc_id = obj.doc_id;
		user_id = obj.user_id;
		NoOfPages = obj.NoOfPages;
		next = obj.next;
	}
	return *this;
}
Document::~Document()
{
}

/*************************************   class QUEUE    ***************************************/

Queue::Queue()
{
	size = 0;
	cur = NULL;
	head = NULL;
	tail = NULL;
}

bool Queue::queueEmpty()const
{
	return (head == NULL);
}

const Queue& Queue::operator=(const Queue& obj) {

	Document* temp = obj.head;
	if (this != &obj)
	{
		for (int i = 0; i < obj.size; i++)
		{
			this->Enqueue(temp->doc_id,temp->user_id, temp->NoOfPages);
			temp = temp->next;
		}
	}
	return *this;
}

void Queue::Enqueue(string d, string n,int f)
{
	if (queueEmpty())
	{
		head = new Document;
		head->doc_id = d;
		head->user_id = n;
		head->NoOfPages = f;
		head->next = NULL;
		tail = head;
		size++;
		return;
	}
	Document* temp = new Document;
	tail->next = temp;
	temp->doc_id = d;
	temp->user_id = n;
	temp->NoOfPages = f;
	temp->next = NULL;
	tail = temp;
	size++;
	return;
}

Document* Queue::Dequeue()
{
	if (queueEmpty())
	{
		cout << "Queue is Empty" << endl;
		return NULL;
	}
	Document* temp = head;
	head = head->next;
	return temp;
}

void Queue::clear()
{
	if (queueEmpty())
	{
		cout << "List is Already cleared" << endl;
		return;
	}
	Document* temp;
	temp = head;
	while (temp != NULL)
	{
		head = head->next;
		delete temp;
		size--;
		temp = head;
	}
	head = tail;
	return;

}
void Queue::display()const
{
	if (queueEmpty() == false)
	{
		Document* currNode = head;
		while (currNode != NULL)
		{
			cout << "USER_ID : " << currNode->user_id << "   |  DOC_ID : " << currNode->doc_id << "  |  No of Pages : " << currNode->NoOfPages << endl;
			currNode = currNode->next;
		}

	}
}
int Queue::getLength()
{
	int numOfItems = 0;
	Document* temp = head;
	while (temp != NULL)
	{
		numOfItems++;
		temp = temp->next;
	}
	return numOfItems;
}

Queue::~Queue()
{
	Document* temp;
	temp = head;
	while (temp != NULL)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}