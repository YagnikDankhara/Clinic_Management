#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
int inputInt(void)
{
    int value;
    char newLine;

    do
    {
        scanf(" %d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

    return value;
}

int inputIntPositive(void)
{
    int value;
    char newLine;

    do
    {
        scanf(" %d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

        if (value < 1)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (newLine != '\n' || value < 1);

    return value;
}

int inputIntRange(int minRange, int maxRange)
{
    int value;

    do
    {
        value = inputInt();

        if (value < minRange || value > maxRange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", minRange, maxRange);
        }
    } while (value < minRange || value > maxRange);

    return value;
}

char inputCharOption(const char validChar[])
{
    char chosenChar;
    int charIsValid = 0;
    int i;

    do
    {
        scanf(" %c", &chosenChar);

        for (i = 0; validChar[i] != '\0'; i++)
        {
            if (validChar[i] == chosenChar)
            {
                charIsValid++;
            }
        }
        if (charIsValid == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", validChar);
        }
    } while (charIsValid == 0);

    clearInputBuffer();
    return chosenChar;
}

void inputCString(char *CString, int minNumOfChar, int maxNumOfChar)
{
    int checkInvalStr = 1;

    while (checkInvalStr)
    {
        int count = 0;
        char charInput = ' ';

        while (charInput != '\n' && count <= maxNumOfChar)
        {
            charInput = getchar();
            CString[count] = charInput;

            if (charInput != '\n')
            {
                count++;
            }
        }

        if (charInput == '\n' && count <= maxNumOfChar)
        {
            CString[count] = '\0';
        }
        // '\0' and flush the exceeding characters.
        else
        {
            CString[maxNumOfChar] = '\0';
            clearInputBuffer();
        }

        if (minNumOfChar == maxNumOfChar && count != minNumOfChar)
        {
            // printf("ERROR: String length must be exactly %d chars: ", minNumOfChar);
            printf("Invalid 10-digit number! Number: ");
        }
        else if (count > maxNumOfChar)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxNumOfChar);
        }
        else if (count < minNumOfChar)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minNumOfChar, maxNumOfChar);
        }
        else
        {
            checkInvalStr = 0;
        }
    }

    return;
}

void displayFormattedPhone(const char *phoneNumber)
{
    int count = 0, i = 0;

    count = strlen(phoneNumber);

    if (count == 10)
    {
        i = 0;
        printf("(");
        while (i < 3)
        {
            printf("%c", phoneNumber[i]);
            i++;
        }
        printf(")");
        while (i < 6)
        {
            printf("%c", phoneNumber[i]);
            i++;
        }
        printf("-");
        while (i < 10)
        {
            printf("%c", phoneNumber[i]);
            i++;
        }
    }
    else
    {
        printf("(___)___-____");
    }
    if (phoneNumber != 0)
    {
        for (i = 0; phoneNumber[i] != '\0'; i++)
            count++;
    }

    return;
}

//

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
