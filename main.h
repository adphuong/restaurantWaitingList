/********************************************************************
 *	File:			main.h
 *	Assignment: 	02 - Stacks & Queues for Restaurant Waiting List
 *	Author:			April Phuong
 *	Date:			May 2, 2021
 *	Description:	This is the header file for main
 *******************************************************************/

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
void execute(char input, Queue & aQueue, int & pos, Stack & aStack);

void addToWaitlist(Queue & aQueue, int & pos);
void seatGroup(Queue & aQueue, int & pos, Stack & aStack);
void checkNextGroup(Queue & aQueue);
void sendPromo(Stack & aStack);
void peekStack(Stack & aStack);

#endif
