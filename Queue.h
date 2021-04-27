#ifndef QUEUE_H
#define QUEUE_H

#include "Group.h"

class Queue {
	public:
		Queue();
		Queue(const Queue & aQueue);
		
		Queue& operator= (const Queue & aQueue);
	 	
		void loadData(const char * filename);
		bool enqueue(const Group & aGroup);
		bool dequeue(Group & aGroup);
		bool peek(Group &aGroup) const;
		bool isEmpty() const;
		void display() const;

		int getSize() const;

	private:
		struct Node {
			Node(const Group & aGroup) {
				data = new Group(aGroup);
				rear = nullptr;
			}
			~Node() {
				delete groupData;
			}

			Group * data;
			Node * rear;
		};

		Node *head, *tail;
		int size;

		void copy(Node * fromHead, Node *& toHead, Node *& toTail);
		void destroy(Node *& first);
};

