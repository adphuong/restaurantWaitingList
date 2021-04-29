#include "Queue.h"

Queue::Queue() : head(nullptr), tail(nullptr), size(0) {}

Queue::Queue(const Queue & aQueue) {
	this->size = aQueue.size;

	copy(aQueue.head, this->head);
}

void Queue::copy(Node * fromHead, Node *& toHead) {
	Node * currFrom;
	Node * currTo;

	if (!fromHead) {
		toHead = nullptr;
		return;
	}

	toHead = new Node(*(fromHead->data));

	currFrom = fromHead->next;
	currTo = toHead;

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

		Group tempGroup(position, groupName, num, isSpecial, specialInfo, isOptedIn);
		addToQueue(tempGroup);
	}

	inFile.close();
}


void Queue::addToQueue(Group & aGroup) {
	Node * temp = nullptr;
	Node * headRef = head;
	Node * prev;
	Node * curr;
	Node * nodeToAdd = new Node(aGroup);

	if (head == nullptr) {
		head = nodeToAdd;
		tail = nodeToAdd;

		head->next = head;
		tail->next = head;

		++size;
	}
	else {
		if (nodeToAdd->data->getPosition() < head->data->getPosition()) {
			temp = head;
			head = nodeToAdd;
			head->next = temp;
		
			tail->next = head;

			++size;
		}
		else if (nodeToAdd->data->getPosition() > tail->data->getPosition()) {
			tail->next = nodeToAdd;
			tail = nodeToAdd;

			++size;
		}
		else {
			prev = head;
			curr = head->next;
			
			// while (Curr != nullptr)
			while (curr != headRef) {
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
	Node * front = head;
	Node * rear = tail;
	Node * newNode = new Node(aGroup);
	bool isAdded = false;

	if (!front) {
		head = tail = newNode;
		head->next = tail->next = head;
		
		isAdded = true;
	}
	else {
		rear->next = newNode;
		rear = newNode;

		rear->next = head;

		isAdded = true;
	}

	return isAdded;
}


bool Queue::dequeue() {
	bool result = false;
	int pos;
	Node * curr;

	if (head) {
		// Not empty, remove from front
		Node * nodeToDelete = tail->next; 

		// Special Case: one node in queue
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			head = head->next;
			tail->next = head;			// THIS BUG TOOK FOREVER TO FIX
		}

		// Update positions for groups currently in waitlist
		curr = head;
		while (curr->next != head) {
			pos = curr->data->getPosition();
			curr->data->setPosition(--pos);

			curr = curr->next;

			//if (curr == head)
			//	break;
		} 
	
		// Updates the last node's position
		pos = curr->data->getPosition();
		curr->data->setPosition(--pos);

		// Delete the first node
		nodeToDelete->next = nullptr;
		delete nodeToDelete;
		nodeToDelete = nullptr;

		result = true;
	}
	return result;
}


ostream & operator<< (ostream & out, const Queue & aQueue) {
	aQueue.printAll(out);

	return out;
}

void Queue::printAll(ostream & out) const {
	Node * curr = head;

	cout << setfill(' ') << setw(8) << left << "#"
		 << setw(20) << left << "GROUP NAME" 
		 << setw(12) << left << "# PEOPLE" 
		 << setw(15) << left << "SPECIAL SEAT"
		 << setw(30) << left << "INFO"
		 << setw(20) << left << "OPT-IN PROMOS" << endl;

	cout << setfill('-') << setw(100) << "-" << endl;
	
	while (head != nullptr) {
		out << *(curr->data) << endl;
		curr = curr->next;

		if (curr == head)
			break;
	}

	/*
	for (curr = head; curr->next != headRef; curr = curr->next) {
		out << *(curr->data) << endl;
	}
	*/

	cout << setfill('-') << setw(100) << "-" << endl;

}
