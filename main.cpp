/********************************************************************
 *	File:			main.cpp
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This program keeps track of a restaurant's 
 *					waiting list. It utilizes a circular linked list
 *					to build, traverse, add, and remove from the 
 *					Queue of groups and also a dynamic array to keep
 *					track of a Stack of people who opt in to be on the 
 *					contact list for promotional material.
 *					Queue, Group, Stack, and ContactInfo are the ADTs
 *					utilized in this menu-driven program.
 *					The user will be able to perform the following:
 *						- Add new group to queue
 *						- Check next group in queue to be seated
 *		 				- Seat a group
 *		 				- Display the waitlist
 *		 				- Peek at top of Promo Opt-in stack
 *						- Send promotion to recent group
 *						- Display contacts in Promo opt-in list
 *******************************************************************/

#include "main.h"

int MAX = 101;
int main() {
	Queue aQueue;
	int count;
	char command;
	char filename[] = "queueData.txt";

	welcome();
	aQueue.loadData(filename);

	// Initializing stack size to 0 since we are dynamically allocating
	Stack aStack(0);

	// Get size of queue and print
	count = aQueue.getSize();
	successLoad(count);

	// Print queue list and menu, then get command from user
	cout << aQueue << endl;
	displayMenu();
	command = getCommand();

	while (command != 'q') {
		execute(command, aQueue, count, aStack);
		displayMenu();
		command = getCommand();
	}

	return 0;
}


/************************** welcome() *******************************
 *  Displays welcome message to user
 *
 *	@params - none 
 *	@returns - none 
 *******************************************************************/
void welcome() {
	cout << endl;

	cout << "Hello! Welcome to My Fancy Restaurant." << endl;
}


/************************** successLoad() **************************
 *  Displays success message if queue was loaded
 *
 *	@params - size of queue 
 *	@returns - none 
 *******************************************************************/
void successLoad(int size) {
	cout << endl
		 << setfill('*') << setw(100) << "*" << endl
		 << "There are currently " << size << " groups on the waiting list." << endl
		 << setfill('*') << setw(100) << "*" 
		 << endl << endl;
}


/************************** displayMenu() **************************
 *  Displays menu options
 *
 *	@params - none 
 *	@returns - none 
 *******************************************************************/
void displayMenu() {
	cout << setfill('-') << setw(100) << "-" << endl
		 << "What would you like to do?" << endl
		 << "[A] Add a group to the waitlist" << endl
		 << "[B] Check next group in queue to be seated" << endl
		 << "[C] Seat a group" << endl
		 << "[D] Display the waitlist" << endl
		 << "[E] Peek at top of Promo Opt-in stack" << endl
		 << "[F] Send promotion to recent group" << endl
		 << "[G] Display contacts in Promo opt-in list" << endl
		 << "[Q] Quit program" << endl
		 << setfill('-') << setw(100) << "-" << endl;

}


/************************** displayMenu() **************************
 *  Prompts user to enter a command to execute 
 *
 *	@params - none 
 *	@returns - none 
 *******************************************************************/
char getCommand() {
	char input;

	cout << "Please pick a command from the menu (A, B, C, D, Q): ";
	cin >> input;

	cin.ignore(100, '\n');
	cout << endl;

	return tolower(input);
}


/**************************** execute() *****************************
 *  Executes the command chosen by user 
 *
 *	@params - input, aQueue, and aStack to pass into functions 
 *	@returns - none 
 *******************************************************************/
void execute(char input, Queue & aQueue, int & pos, Stack & aStack) {
	switch (input) {
		case 'a':
			addToWaitlist(aQueue, pos);
			break;
		case 'b':
			checkNextGroup(aQueue);	
			break;
		case 'c':
			seatGroup(aQueue, pos, aStack);
			break;
		case 'd':
			cout << aQueue << endl;
			break;
		case 'e':
			peekStack(aStack);	
			break;
		case 'f':
			sendPromo(aStack);
			break;
		case 'g':
			cout << aStack << endl;
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


/************************** addToWaitlist() ************************
 *  Prompts user for group name, num of people, if they want special 
 *	seating, special seating info if yes, if they want to opt-in 
 *	for promo materials. Then stores in temp variables. Queue's 
 *	enqueue will be called with the group data to add to the queue.
 *
 *	@params - aQueue and pos (keeps track of each group's num in line) 
 *	@returns - none 
 *******************************************************************/
void addToWaitlist(Queue & aQueue, int & pos) {
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


/************************** seatGroup() *****************************
 *  Before seating group, user will be prompted for contact info if 
 *	they opted-in for it earlier. The new contact info will be pushed
 *	to the stack and Queue's dequeue will be called to seat the group.
 *
 *	@params - aQueue, aStack, and pos (keeps track of each group's num in line) 
 *	@returns - none 
 *******************************************************************/
void seatGroup(Queue & aQueue, int & pos, Stack & aStack) {
	Group groupToSeat = aQueue.peek();
	char fullName[MAX_CHAR];
	char email[MAX_CHAR];

	// Prompt for contact info to add to stack
	if (groupToSeat.getOptedIn()) {
		cout << "Our records indicate that you opted in for our promo mailing list!" 
			 << endl << endl
			 << "Please enter your contact info below:" << endl;
		
		cout << "Full Name: ";
		cin.getline(fullName, MAX_CHAR);

		cout << "Email Address: ";
		cin.getline(email, MAX_CHAR);

		ContactInfo tempContact(fullName, email);

		aStack.push(tempContact);	
	}

	// Seat group
	bool isSeated = aQueue.dequeue(pos);
	
	if (isSeated) {
		cout << endl;
		cout << "GROUP HAS BEEN SEATED!" << endl << endl;
	}

	else {
		cout << "Oops, looks like the group has to wait a little longer!" 
		 	 << endl;
	}
}



/************************** checkNextGroup() **************************
 *  Queue's peek() is called to check the group that is next in line
 *
 *	@params - aQueue 
 *	@returns - none 
 *******************************************************************/
void checkNextGroup(Queue & aQueue) {
	Group nextGroup = aQueue.peek();

	cout << "THE NEXT GROUP TO BE SEATED IS: " << endl << endl;
	
	cout << setfill(' ') << setw(8) << left << "#"
		 << setw(20) << left << "GROUP NAME" 
		 << setw(12) << left << "# PEOPLE" 
		 << setw(15) << left << "SPECIAL SEAT"
		 << setw(30) << left << "INFO"
		 << setw(20) << left << "OPT-IN PROMOS" << endl;

	cout << setfill('-') << setw(100) << "-" << endl
		 << nextGroup << endl
		 << setfill('-') << setw(100) << "-" << endl;

	cout << endl;

	
}


/************************** sendPromo() ****************************
 *  Stack's pop() will be called to send promo to contact at the top
 *	of the stack

 *	@params - aStack 
 *	@returns - none 
 *******************************************************************/
void sendPromo(Stack & aStack) {
	bool promoSent = false;

	promoSent = aStack.pop();

	if (!promoSent) {
		cout << "Looks like there are no contacts in this list "
			 << "to send promotions to right now."
			 << endl << endl;
	}
}


/************************** peekStack() ****************************
 *  Stack's peek() will be called to print the contact info at the top
 *	of the stack

 *	@params - aStack 
 *	@returns - none 
 *******************************************************************/
void peekStack(Stack & aStack) {
	bool topFound;

	topFound = aStack.peek();

	if (!topFound) {
		cout << "There are currently no contacts on the stack list." 
			 << endl << endl;
	}
}
