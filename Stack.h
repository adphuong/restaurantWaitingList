#ifndef STACK_H
#define STACK_H
#include "ContactInfo.h"

const int CAPACITY = 101;
class Stack {
	public:
		Stack();
		Stack(const Stack & aStack);
		
		Stack& operator= (const Stack & aStack);
	 	
		bool push(const ContactInfo & aPerson);
		bool pop(ContactInfo & aPerson);
		bool peek(ContactInfo & aPerson) const;
		bool isEmpty() const;
		void display() const;

		int getSize() const;
		const char * getFullName() const;
		const char * getEmail() const;

	private:
		ContactInfo * persons[CAPACITY];	
		int size;

};

#endif
