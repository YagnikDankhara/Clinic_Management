#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int min, int max);

char inputCharOption(const char validChar[]);

void inputCString(char *string, int min, int max);

void displayFormattedPhone(const char *string);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
