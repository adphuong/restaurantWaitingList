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
	Node * prev;
	Node * curr;
	Node * nodeToAdd = new Node(aGroup);

	if (head == nullptr) {
		head = nodeToAdd;
		tail = nodeToAdd;

		++size;
	}
	else {
		if (nodeToAdd->data->getPosition() < head->data->getPosition()) {
			temp = head;
			head = nodeToAdd;
			head->next = temp;

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

			while (curr != nullptr) {
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


ostream & operator<< (ostream & out, const Queue & aQueue) {
	aQueue.printAll(out);

	return out;
}

void Queue::printAll(ostream & out) const {
	Node *curr = head;

	cout << setfill(' ') << setw(15) << left << "# IN LINE"
		 << setw(20) << left << "GROUP NAME" 
		 << setw(12) << left << "# PEOPLE" 
		 << setw(15) << left << "SPECIAL SEAT"
		 << setw(30) << left << "INFO"
		 << setw(20) << left << "OPT-IN PROMOS" << endl;

	cout << setfill('-') << setw(100) << "-" << endl;

	for (curr = head; curr; curr = curr->next) {
		out << *(curr->data) << endl;
	}

	cout << setfill('-') << setw(100) << "-" << endl;

}
