/********************************************************************
 *	File:			Queue.cpp
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This includes all the implementations for the 
 *					Queue ADT:
 *					- Default constructor & Copy Constructor
 *					- Destructor
 *					- Getter: getSize() & loadData()
 *					- Overloaded (=) and (<<) operators
 *					- Queue operations: 
 *						- enqueue(), dequeue(), peek()
 *					- Private member functions:
 *						- addToQueue(), printAll(), copy(), destroy()
 *******************************************************************/

#include "Queue.h"

/*************************** Queue() *******************************
 *	Default constructor
 *
 *	@params - none
 *	@returns - none
 *******************************************************************/
Queue::Queue() : front(nullptr), back(nullptr), size(0) {}


/*************************** Queue() *******************************
 *	Copy constructor that takes in address of a Queue object and 
 *	copies data from it. 
 *
 *	@params - address of Queue we want copy from
 *	@returns - Queue object with copied data
 *******************************************************************/
Queue::Queue(const Queue & aQueue) {
	this->size = aQueue.size;

	copy(aQueue.front, this->front);
}


/*************************** ~Queue() *******************************
 *	Destructor to return memory
 *
 *	@params - pointer of node we want to destroy
 *	@returns - none
 *******************************************************************/
Queue::~Queue() {
	destroy(this->front);
}


/*************************** destroy() *****************************
 *	Helper function for destructor to release memory
 *
 *	@params - pointer of node we want to destroy
 *	@returns - none
 *******************************************************************/
void Queue::destroy(Node *& first) {
	Node * curr = first;
	Node * next = front->next;

	if (next) {
		curr->next = nullptr;
	}
	curr = next;

	while (curr) {
		next = curr->next;
		delete curr;

		curr = next;
	}

	front = nullptr;
	back = nullptr;
}


/*************************** copy() *********************************
 *	Copies data from one node to another using pass by reference
 *	
 *	@params - pointer of node we want to copy from and address of 
 *			  pointer we want to copy to
 *	@returns - none
 *******************************************************************/
void Queue::copy(Node * fromFront, Node *& toFront) {
	Node * currFrom;
	Node * currTo;

	// Empty list we are copying from
	if (!fromFront) {
		toFront = nullptr;
		return;
	}

	// Copy first piece of data in fromFront
	toFront = new Node(*(fromFront->data));

	// First node already copied
	currFrom = fromFront->next;
	currTo = toFront;

	// While there is something to copy
	while (currFrom) {
		// Create new node
		currTo->next = new Node(*(currFrom->data));

		// update for traversing
		currFrom = currFrom->next;
		currTo = currTo->next;
	}
}

int Queue::getSize() const {
	return size;
}


/*************************** loadData() *****************************
 *	Loads the list of groups into our queue
 *	
 *	@params - pointer to char filename that we want to load
 *	@returns - none
 *******************************************************************/

void Queue::loadData(const char * filename) {
	int position;
	char groupName[MAX_CHAR];
	int num;
	bool isSpecial;
	char specialInfo[MAX_CHAR];
	bool isOptedIn;

	ifstream inFile;
	inFile.open(filename);

	if (!inFile) {
		cerr << "File failed to open " << filename << " for reading!"
			 << endl;
		exit(1);
	}

	// Read data from file
	while (inFile.getline(groupName, MAX_CHAR, ',')) {
		inFile >> position; 
		inFile.get();
		
		inFile >> num;
		inFile.get();

		inFile >> isSpecial;
		inFile.get();

		inFile.getline(specialInfo, MAX_CHAR, ',');

		inFile >> isOptedIn;
		inFile.ignore();

		/*
		if (isOptedIn) {
			++numPromos;
		}
		*/

		// Create group object so that we can add to queue
		Group tempGroup(position, groupName, num, isSpecial, specialInfo, isOptedIn);
		addToQueue(tempGroup);
	}

	inFile.close();
}


/*************************** addToQueue() ***************************
 *	Adds group to the Queue by position number. All new groups that
 *	entered by the user will be added to the back.
 *	
 *	@params - Address of group we want to add
 *	@returns - none
 *******************************************************************/
void Queue::addToQueue(Group & aGroup) {
	Node * temp = nullptr;
	Node * frontRef = front;
	Node * prev;
	Node * curr;
	Node * nodeToAdd = new Node(aGroup);

	// List is empty, so add group to the front
	if (front == nullptr) {
		front = nodeToAdd;
		back = nodeToAdd;

		// Update pointers for circular linked list
		front->next = front;
		back->next = front;

		++size;
	}
	// There is at least one group in the list
	else {
		// Add group to the front 
		if (nodeToAdd->data->getPosition() < front->data->getPosition()) {
			temp = front;
			front = nodeToAdd;
			front->next = temp;
		
			back->next = front;

			++size;
		}
		// Add group to the back
		else if (nodeToAdd->data->getPosition() > back->data->getPosition()) {
			back->next = nodeToAdd;
			back = nodeToAdd;

			back->next = front;

			++size;
		}
		// There are at least 2 groups already in list if we reach here,
		// so we will be adding it somewhere in the list
		else {
			prev = front;
			curr = front->next;
			
			while (curr != frontRef) {
				if (nodeToAdd->data->getPosition() < curr->data->getPosition())
				{
					prev->next = nodeToAdd;
					nodeToAdd->next = curr;
					
					if (nodeToAdd->next == back) {
						back->next = front;
					}

					break;
				}
				else {
					prev = curr;
					curr = curr->next;
				}
			}
			++size;
		}
	}
}


/*************************** enqueue() *****************************
 *	Add new group/node to the Queue
 *	
 *	@params - Address of group we want to add
 *	@returns - true if added successfully, false otherwise
 *******************************************************************/
bool Queue::enqueue(const Group & aGroup) {
	Node * newNode = new Node(aGroup);

	return enqueue(newNode, front);
}


/********************* Recursive enqueue() **************************
 *	Recursive function to add a group to the queue
 *	
 *	@params - pointer to node we want to add
 *			- pointer to current head
 *	@returns - true if added successfully, false otherwise
 *******************************************************************/
bool Queue::enqueue(Node * newNode, Node * front) {
	if (!front) {
		front = back = newNode;
		front->next = back->next = front;
		
		return true;
	}
	else {
		back->next = newNode;
		back = newNode;

		back->next = front;

		return true;
	}

	return enqueue(newNode, front->next);
	
}


/*************************** dequeue() *****************************
 *	Remove group from front of the queue
 *	
 *	@params - address of an int (pos) to update position nums
 *	@returns - true if removed successfully, false otherwise
 *******************************************************************/
bool Queue::dequeue(int & pos) {
	bool result = false;
	int newPos;
	Node * curr;

	if (front) {
		// Not empty, remove from front
		Node * nodeToDelete = back->next; 

		// Special Case: one node in queue
		if (front == back) {
			front = nullptr;
			back = nullptr;
		}
		else {
			front = front->next;
			back->next = front;			// THIS BUG TOOK FOREVER TO FIX

			--pos;
		}

		// Update positions for groups currently in waitlist
		curr = front;
		while (curr->next != front) {
			newPos = curr->data->getPosition();
			curr->data->setPosition(--newPos);

			curr = curr->next;

			//if (curr == front)
			//	break;
		} 
	
		// Updates the last node's position
		newPos = curr->data->getPosition();
		curr->data->setPosition(--newPos);

		// Delete the first node
		nodeToDelete->next = nullptr;
		delete nodeToDelete;
		nodeToDelete = nullptr;

		result = true;
	}
	return result;
}


/****************************** peek() ******************************
 *	Get group that is in front of the queue
 *	
 *	@params - none
 *	@returns - Group object that is at the front of queue
 *******************************************************************/
Group Queue::peek() const {
	if (front == nullptr) {
		cout << "peek() called with empty queue." << endl;
	}

	return *(front->data);
}


/*********************** Overloaded << operator *********************
 *	Overloading << operator so client can print Queue object.
 *	
 *	@params - address of ostream and queue we want to print
 *	@returns - ostream we want to print
 *******************************************************************/
ostream & operator<< (ostream & out, const Queue & aQueue) {
	aQueue.printAll(out);

	return out;
}

void Queue::printAll(ostream & out) const {
	Node * curr = front;

	cout << setfill(' ') << setw(8) << left << "#"
		 << setw(20) << left << "PARTY NAME" 
		 << setw(12) << left << "# PEOPLE" 
		 << setw(15) << left << "SPECIAL SEAT"
		 << setw(30) << left << "INFO"
		 << setw(20) << left << "OPT-IN PROMOS" << endl;

	cout << setfill('-') << setw(100) << "-" << endl;
	
	while (front != nullptr) {
		out << *(curr->data) << endl;
		curr = curr->next;

		if (curr == front)
			break;
	}

	cout << setfill('-') << setw(100) << "-" << endl;

}
