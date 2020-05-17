#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "ListBasedSet.h"
#include "Header.h"

using namespace std;
int main()
{

//Step1: Read printer.txt and store in printer_array

	int i = 0;
	char letter = ' ';
	ifstream myfile("printer.txt");
	if (myfile.is_open())
	{
		myfile >> noskipws;
		while (!myfile.eof())
		{
			myfile >> letter;
			if (letter == ' ')
			{
				i++;
			}
			if (letter == '\n')
			{
				i++;
			}
		}
	}
	else cout << "Unable to open file." << endl;
	myfile.close();
	i = i+2;
	
	string* printer_array = new string[i];
	string file_string, s;
	int j = 0, printercount = 0;
	ifstream myfile1("printer.txt");
	if (myfile1.is_open())
	{
		
		while (getline(myfile1, file_string))
		{
			stringstream ss(file_string);
			while (getline(ss, s, ' '))
			{
				printer_array[j] = s;
				j++;
			}
			printercount++;
		}
	}
	else cout << "Unable to open file." << endl;
	myfile1.close();
	j++;

//Step2: Read user.txt and store in user_array

	int k = 0;
	char letter1 = ' ';
	ifstream myfile2("user.txt");
	if (myfile2.is_open())
	{
		myfile2 >> noskipws;
		while (!myfile2.eof())
		{
			myfile2 >> letter1;
			if (letter1 == ' ')
			{
				k++;
			}
			if (letter1 == '\n')
			{
				k++;
			}
		}
	}
	else cout << "Unable to open file." << endl;
	myfile2.close();
	k = k + 2;

	string* user_array = new string[k];
	string file_string1, s1;
	int l = 0, usercount = 0;
	ifstream myfile3("user.txt");
	if (myfile3.is_open())
	{
		while (getline(myfile3, file_string1))
		{
			stringstream ss1(file_string1);
			while (getline(ss1, s1, ' '))
			{
				user_array[l] = s1;
				l++;
			}
			usercount++;
		}
	}
	else cout << "Unable to open file." << endl;
	myfile3.close();
	l++;


//Step3: Make User's List and insert data in it.

	Userlist users;

	int a = 0, b = 3, c = 0;
	for (int j = 0; j < usercount; j++)
	{
		User temp;
		temp.user_id = user_array[a];
		a++;
		temp.priority = stoi(user_array[a]);
		a++;
		c = stoi(user_array[a]);
		for (int i = 0; i < c; i++)
		{
			temp.doc_queue.Enqueue(user_array[b], temp.user_id , stoi(user_array[b + 1]));
			b = b + 2; ;
			a = a + 2;
		}
		users.insert(temp);
		a++;
		b = b + 3;
	}

	//users.display();

//Step4: Make PrinterList and insert data in it.

	PrinterList printers;
	int d = 0;
	for (int j = 0; j < printercount; j++)
	{
		Printer temp;
		temp.printer_id = printer_array[d];
		d++;
		temp.maximum_capacity = stoi(printer_array[d]);
		d++;
		printers.insert(temp);
	}
	//printers.display();


//Step5: Make Printer Spooler and perform INSERTION and DELETION.

	users.pointer = users.head;
	while (!users.isEmpty())
	{
		while (!users.getPriorUser()->doc_queue.queueEmpty())
		{
			Document* temp3 = users.getPriorUser()->doc_queue.Dequeue();

			Printer* temp2 = printers.getSuitablePrinter(temp3);
			temp2->u.Enqueue(temp3->doc_id, temp3->user_id, temp3->NoOfPages);
		}

		users.removeUser(users.getPriorUser()->priority);
	}

	

//Step6: Write output in out.txt.

	cout << endl << endl << "//**********************************************************************************************//" << endl;
	cout << "//                                         PRINTER SPOOLER                                      //" << endl;
	cout << "//**********************************************************************************************//" << endl << endl;
	printers.display();
	printers.clear();
	return 0;

}


















