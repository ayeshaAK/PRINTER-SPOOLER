#pragma once
#include<iostream>
#include<cstring>
#include"Header.h"
using namespace std;

//*************************************** NODE CLASS USER ***************************************************//

class User {
public:
	string user_id;
	int priority;
	Queue doc_queue;
	User* next;
	User() : user_id(""), priority(0), doc_queue(), next(NULL)
	{}
	User(const User& obj)
	{
		*this = obj;
	}
	const User& operator=(const User& obj)
	{
		if (this != &obj)
		{
			user_id = obj.user_id;
			priority = obj.priority;
			doc_queue = obj.doc_queue;
			next = obj.next;
		}
		return *this;
	}
	void display()const
	{
		cout << "USER_ID : " << user_id << " |  PRIORITY : " << priority << endl;
		this->doc_queue.display();
	}
	~User() {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Userlist
{
public:
	//set based on linked list, returns false on insertion if element is already present
	User* head;
	User* pointer;
	Userlist() :head(NULL), pointer(NULL)
	{}
	~Userlist()
	{
		User* currNode = head;
		User* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; 
			currNode = nextNode;
		}
	}
	Userlist(const Userlist& obj)
	{
		head = NULL;
		*this = obj;
	}
	const Userlist& operator=(const Userlist& obj)
	{
		if (this != &obj)
		{
			clear();
			User* curr = obj.head;
			while (curr)
			{
				insert(*curr);
				curr = curr->next;
			}
		}
		return *this;
	}
	bool isEmpty()const
	{
		return (head == NULL);
	}
	bool removeUser(int index)
	{
		User* prevNode = NULL;
		User* currNode = head;
		while (currNode && !(currNode->priority == index)) 
		{
			prevNode = currNode;
			currNode = currNode->next;
		}
		if (currNode == NULL) 
		{
			return false;
		}
		if (prevNode) {
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		return true;
	}

	int min()
	{
		if (head)
		{
			int min = head->priority;
			User* temp = head;
			while (temp)
			{
				if (min>(temp->priority))
				{
					min = temp->priority;
				}
				temp = temp->next;
			}
			return min;
		}
	}
	int max()
	{
		if (head)
		{
			int max = head->priority;
			User* temp = head;
			while (temp)
			{
				if (max < (temp->priority))
				{
					max = temp->priority;
				}
				temp = temp->next;
			}
			return max;
		}
	}
	User* getPriorUser()
	{
		int prior = this->max();
		if (prior < 0)
			return NULL;

		if (!head)
			return NULL;
		
		User* node = head;
		while (node != NULL && node->priority != prior) 
		{
			node = node->next;
		}
		if (node == NULL)
		{
			return NULL;
		}
		else
		{
			return (node);
		}
	}
	void display()const
	{
		if (isEmpty() == false)
		{
			User* currNode = head;
			while (currNode != NULL)
			{
				cout << "USER_ID : " << currNode->user_id << " |  PRIORITY : " << currNode->priority << endl;
				currNode->doc_queue.display();
				cout << endl << endl;
				currNode = currNode->next;
			}
		}
	}
	void clear()
	{
		User* currNode = head;
		User* cl = NULL;
		while (currNode != NULL) {
			cl = currNode;
			currNode = currNode->next;
			delete cl;
		}
		head = NULL;
	}

	bool insert(const User obj)
	{
		User* previous = NULL;
		User* currNode = head;
		while (currNode != NULL)
		{
			if (currNode->user_id == obj.user_id)
			{ // redundancy check
				return false;
			}
			previous = currNode;
			currNode = currNode->next;
		}
		User* newNode = new User(obj);
		if (currNode == head)
		{
			head = newNode;
		}
		else
		{
			previous->next = newNode;
		}
		return true;
	}
};

//********************************** NODE CLASS PRINTER ************************************************//

class Printer {
public:
	string printer_id;
	Queue u;
	double current_load;
	double maximum_capacity;
	double available_capacity;
	Printer* next; 
	Printer()
	{
		printer_id = "\0";
		current_load = 0;
		maximum_capacity = -1;
		available_capacity = -1;
		next = NULL;
	}
	Printer(string p, Queue u, double cl, double mc, double ac) :printer_id(p), u(u), current_load(cl), maximum_capacity(mc), available_capacity(ac), next(NULL) {}
	Printer(const Printer& obj)
	{
		*this = obj;
	}
	void display()const
	{
		cout << "PRINTER_ID : " << printer_id << " |  MAX_CAPACITY : " << maximum_capacity << endl << "CURRENT_LOAD : " << current_load << " |  AVAIL_CAPACITY : " << available_capacity << endl << endl;
	}
	void setAvailableCapacity(int pages)
	{
		available_capacity = available_capacity - pages;
		if (available_capacity < 0)
		{
			available_capacity = 0;
		}
	}
	void setCurrentLoad(double pages)
	{
		current_load = current_load + (pages/maximum_capacity) * 100;
		if (current_load >= 100)
		{
			cout << "Printer Load is 100%" << endl;
			current_load = 100;
		}
	}
	const Printer& operator=(const Printer& obj)
	{
		if (this != &obj)
		{
			printer_id = obj.printer_id;
			u = obj.u;
			current_load = obj.current_load;
			maximum_capacity = obj.maximum_capacity;
			available_capacity = obj.available_capacity;
			next = obj.next;
		}
		return *this;
	}
	~Printer() {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PrinterList
{
public:
	//set based on linked list, returns false on insertion if element is already present
	Printer* head;
	Printer* pointer;
	PrinterList() :head(NULL), pointer(NULL)
	{}
	~PrinterList()
	{
		Printer* currNode = head;
		Printer* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode;
			currNode = nextNode;
		}
	}
	PrinterList(const PrinterList& obj)
	{
		head = NULL;
		*this = obj;
	}
	const PrinterList& operator=(const PrinterList& obj)
	{
		if (this != &obj)
		{
			clear();
			Printer* curr = obj.head;
			while (curr)
			{
				insert(*curr);
				curr = curr->next;
			}
		}
		return *this;
	}
	bool isEmpty()const
	{
		return (head == NULL);
	}
	Printer* getP3()
	{
		if (!head)
			return NULL;

		Printer* node = head;
		while (node != NULL && node->maximum_capacity != -1)
		{
			node = node->next;
		}
		if (node == NULL)
		{
			return NULL;
		}
		else
		{
			return (node);
		}
	}
	Printer* getSuitablePrinter(Document* d)
	{
		Printer* currNode = head;
		while (currNode)
		{
			if (currNode->current_load < 50)
			{
				int ac = currNode->available_capacity - d->NoOfPages;
				if (ac < 0)
				{
					goto label;
				}
				if (currNode->available_capacity >= ac && currNode->available_capacity != 0)
				{
					break;
				}
			}
			label:
			currNode = currNode->next;
		}
		if (currNode == NULL || currNode->available_capacity == -1)
		{
			return(getP3());
		}
		else
		{
			currNode->setAvailableCapacity(d->NoOfPages);
			currNode->setCurrentLoad(d->NoOfPages);
			return currNode;
		}

	}
	bool removePrinter(string id)
	{
		Printer* prevNode = NULL;
		Printer* currNode = head;
		while (currNode && !(currNode->printer_id == id))
		{
			prevNode = currNode;
			currNode = currNode->next;
		}
		if (currNode == NULL)
		{
			return false;
		}
		if (prevNode) {
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		return true;
	}

	void display()const
	{
		if (isEmpty() == false)
		{
			Printer* currNode = head;
			while (currNode != NULL)
			{
				cout << "PRINTER_ID : " <<currNode->printer_id << endl << "MAX_CAPACITY : " <<currNode->maximum_capacity << endl;
				cout << "AVAILABLE_CAPACITY : " << currNode->available_capacity << endl << "CURRENT LOAD : " << currNode->current_load << "%" << endl;
				currNode->u.display();
				cout << endl << endl;
				currNode = currNode->next;
			}
		}
	}
	void clear()
	{
		Printer* currNode = head;
		Printer* cl = NULL;
		while (currNode != NULL) {
			cl = currNode;
			currNode = currNode->next;
			delete cl;
		}
		head = NULL;
	}

	bool insert(const Printer obj)
	{
		Printer* previous = NULL;
		Printer* currNode = head;
		while (currNode != NULL)
		{
			if (currNode->printer_id == obj.printer_id)
			{ // redundancy check
				return false;
			}
			previous = currNode;
			currNode = currNode->next;
		}
		Printer* newNode = new Printer(obj);
		newNode->available_capacity = newNode->maximum_capacity;
		if (currNode == head)
		{
			head = newNode;
		}
		else
		{
			previous->next = newNode;
		}
		return true;
	}

};