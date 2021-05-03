#include "Queue.h"

Queue::Queue() : front(nullptr), back(nullptr), size(0) {}

Queue::Queue(const Queue & aQueue) {
	this->size = aQueue.size;

	copy(aQueue.front, this->front);
}


Queue::~Queue() {
	destroy(this->front);
}


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
}

void Queue::copy(Node * fromfront, Node *& tofront) {
	Node * currFrom;
	Node * currTo;

	if (!fromfront) {
		tofront = nullptr;
		return;
	}

	tofront = new Node(*(fromfront->data));

	currFrom = fromfront->next;
	currTo = tofront;

	while (currFrom) {
		currTo->next = new Node(*(currFrom->data));

		currFrom = currFrom->next;
		currTo = currTo->next;
	}
}

int Queue::getSize() const {
	return size;
}

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

		Group tempGroup(position, groupName, num, isSpecial, specialInfo, isOptedIn);
		addToQueue(tempGroup);
	}

	inFile.close();
}


void Queue::addToQueue(Group & aGroup) {
	Node * temp = nullptr;
	Node * frontRef = front;
	Node * prev;
	Node * curr;
	Node * nodeToAdd = new Node(aGroup);

	if (front == nullptr) {
		front = nodeToAdd;
		back = nodeToAdd;

		front->next = front;
		back->next = front;

		++size;
	}
	else {
		if (nodeToAdd->data->getPosition() < front->data->getPosition()) {
			temp = front;
			front = nodeToAdd;
			front->next = temp;
		
			back->next = front;

			++size;
		}
		else if (nodeToAdd->data->getPosition() > back->data->getPosition()) {
			back->next = nodeToAdd;
			back = nodeToAdd;

			++size;
		}
		else {
			prev = front;
			curr = front->next;
			
			// while (Curr != nullptr)
			while (curr != frontRef) {
				if (nodeToAdd->data->getPosition() < curr->data->getPosition())
				{
					prev->next = nodeToAdd;
					nodeToAdd->next = curr;

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


bool Queue::enqueue(const Group & aGroup) {
	Node * newNode = new Node(aGroup);

	return enqueue(newNode, front);
}


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


Group Queue::peek() const {
	if (front == nullptr) {
		cout << "peek() called with empty queue." << endl;
	}

	return *(front->data);
}


ostream & operator<< (ostream & out, const Queue & aQueue) {
	aQueue.printAll(out);

	return out;
}

void Queue::printAll(ostream & out) const {
	Node * curr = front;

	cout << setfill(' ') << setw(8) << left << "#"
		 << setw(20) << left << "GROUP NAME" 
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
