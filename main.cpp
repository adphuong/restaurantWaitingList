#include "main.h"

int MAX = 101;
int main() {
	Queue aQueue;
	int count;
	char command;
	char filename[] = "queueData.txt";

	welcome();
	aQueue.loadData(filename);

	count = aQueue.getSize();
	successLoad(count);

	cout << aQueue << endl;

	displayMenu();
	command = getCommand();

	while (command != 'q') {
		execute(command, aQueue, count);
		displayMenu();
		command = getCommand();
	}

	/* For stack, to figure out how big our array is for Stack, we want to
	 * check for isOptInPromos is true, if it is, we want to increment our counter.
	 * Then we use this counter to pass into a Stack constructor so it
	 * allocates enough memory for the array size.
	 * When a group is seated, prompt for full and email, create a ContactInfo
	 * object with those two data. Then push this onto the stack with push()
	 *
	 * When enqueue, we want to check if new data for isOptIn = true. If it is,
	 * we increment count and pass in to Stack constructor
	 */


	return 0;
}


void welcome() {
	cout << endl;

	cout << "Hello! Welcome to My Fancy Restaurant." << endl;
}


void successLoad(int size) {
	cout << endl
		 << setfill('*') << setw(100) << "*" << endl
		 << "There are currently " << size << " groups on the waiting list." << endl
		 << setfill('*') << setw(100) << "*" 
		 << endl << endl;
}


void displayMenu() {
	cout << setfill('-') << setw(100) << "-" << endl
		 << "What would you like to do?" << endl
		 << "[A] Add group to the waitlist" << endl
		 << "[B] Seat a group from the waitlist" << endl
		 << "[C] Check who is next in line to be seated" << endl
		 << "[D] Display the waitlist" << endl
		 << "[Q] Quit program" << endl
		 << setfill('-') << setw(100) << "-" << endl;

}


char getCommand() {
	char input;

	cout << "Please pick a command from the menu (A, B, C, D, Q): ";
	cin >> input;

	cin.ignore(100, '\n');
	cout << endl;

	return tolower(input);
}


void execute(char input, Queue & aQueue, int count) {
	switch (input) {
		case 'a':
			addToWaitlist(aQueue, count);
			break;
		
		case 'b':
			aQueue.dequeue();
			break;
/*
		case 'c':
			checkNextGroup(aQueue);
			break;
		*/
		case 'd':
			cout << aQueue << endl;
			break;
		
		case 'q':
			exit(1);
			break;
		default:
			cout << "Oops, looks like that's not a valid option. " 
				 << "Please enter again."
				 << endl << endl;
			break;			
	}
}


void addToWaitlist(Queue & aQueue, int pos) {
	char groupName[MAX_CHAR];
	int num;
	bool specialSeating;
	char seatingInfo[MAX_CHAR];
	bool optInPromos;
	bool isAdded;

	// Get group name
	cout << "Enter your group name: " ;
	cin.getline(groupName, MAX_CHAR);


	// Get num of people and do some checking and clearing
	cout << "Enter the number of people in your group: ";
	cin >> num;
	cin.clear();
	cin.ignore(MAX_CHAR, '\n');

	while (cin.fail() || num < 0) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');

		cout << endl;
		cout << "Invalid input. Please enter number again: ";
		cin >> num;
	}
	

	// Get special seating and check input. Clear buffer
	cout << "Will you need any special seating? (1 = Yes, 0 = No): ";
	cin >> specialSeating;
	cin.clear();
	cin.ignore(MAX_CHAR, '\n');

	while (cin.fail()) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');

		cout << endl;
		cout << "Invalid input. Please enter again (1 = Yes, 0 = No): ";
		cin >> specialSeating;
	}
	

	// Set seatingInfo to 'None' if false, otherwise get input from user
	if (!specialSeating) {
		strcpy(seatingInfo, "None");

	}
	else {
		cout << "Enter special seating (Highchair, Wheelchair, or None): " ;
		cin.getline(seatingInfo, MAX_CHAR);
	}

	// Get input for opt-in for promotions. Clear buffer and do checking
	cout << "Would you like to opt-in for promotional information? "
		 << "(1 = Yes, 0 = No): ";
	cin >> optInPromos;
	cin.clear();
	cin.ignore(MAX_CHAR, '\n');

	while (cin.fail()) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');

		cout << endl;
		cout << "Invalid input. Please enter again (1 = Yes, 0 = No): ";
		cin >> optInPromos ;
	}
	++pos;				// Indicates position in line

	// Create new Group object with new data from user
	Group tempGroup(pos, groupName, num, specialSeating, 
					seatingInfo, optInPromos);

	// Add to back of queue
	isAdded = aQueue.enqueue(tempGroup);

	if (isAdded) {
		cout << endl
		 	 << tempGroup.getGroupName() 
		 	 << " has been successfully added to the waitlist."
		 	 << endl << endl;
	}
	else {
		cout << "Oops, looks like we couldn't add that." << endl;
	}
	
}


