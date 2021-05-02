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
	 	
		int loadData(const char * filename);	
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

		Node *head, *tail;
		int size;
		
		void addToQueue(Group & aGroup);
		void printAll(ostream & out) const;

		void copy(Node * fromHead, Node *& toHead);
		void destroy(Node *& first);
};


#endif
