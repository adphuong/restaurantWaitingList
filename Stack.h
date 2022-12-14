/********************************************************************
 *	File:			Stack.h
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This is the header file for Stack ADT
 *******************************************************************/

#ifndef STACK_H
#define STACK_H
#include "ContactInfo.h"

const int TMP_CAP = 100;

class Stack {
	public:
		Stack();
		Stack(int initSize);
		Stack(const Stack & aStack);
		~Stack();

		Stack& operator= (const Stack & aStack);
	 	
		bool push(const ContactInfo & aPerson);
		bool pop();
		bool peek() const;
		
		int getSize() const;

		friend ostream& operator<< (ostream & out, const Stack & aStack);

	private:
		ContactInfo ** stackOfContacts;	
		int size;
		
		void destroy();
		void copy(Stack & dest, const Stack & src);
		void display(ostream & out) const;

		void saveToFile(ContactInfo & aContact) ;
};

#endif
