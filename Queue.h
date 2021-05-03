/********************************************************************
 *	File:			Queue.h
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This is the header file for Queue ADT
 *******************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "Group.h"

const int MAX_CHAR = 101;

class Queue {
	public:
		Queue();
		Queue(const Queue & aQueue);
		~Queue();

		Queue& operator= (const Queue & aQueue);
	 	
		void loadData(const char * filename);	
		bool enqueue(const Group & aGroup);
		bool dequeue(int & pos);
		Group peek() const;

		int getSize() const;

		friend ostream& operator<< (ostream & out, const Queue & aQueue);

	private:
		struct Node {
			Node(const Group & aGroup) {
				data = new Group(aGroup);
				next = nullptr;
			}
			~Node() {
				delete data;
			}

			Group * data;
			Node * next;
		};

		Node *front, *back;
		int size;
	
		// Recursive function for enqueue
		bool enqueue(Node * newNode, Node * front);

		void addToQueue(Group & aGroup);
		void printAll(ostream & out) const;

		void copy(Node * fromHead, Node *& toHead);
		void destroy(Node *& first);
};


#endif
