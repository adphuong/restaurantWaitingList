#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cctype>

#include "Group.h"
#include "ContactInfo.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

void welcome();
void successLoad(int size);

void displayMenu();
char getCommand();
void execute(char input, Queue & aQueue, int & pos);

void addToWaitlist(Queue & aQueue, int & pos);
void seatGroup(Queue & aQueue, int & pos);

#endif
