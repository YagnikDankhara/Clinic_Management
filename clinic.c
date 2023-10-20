#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

#define STARTING_HOUR 10
#define END_HOUR 14
#define INTERVAL 30

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date *date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// Menu: Appointment Management
void menuAppointment(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments, data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0, ValidRecord = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            ValidRecord = 1;
        }
    }
    if (!ValidRecord)
    {
        printf("*** No records found ***\n\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int Options;

    do
    {
        printf("Search Options\n==========================\n1) By patient number\n2) By phone number\n");
        printf("..........................\n0) Previous menu\n..........................\n");
        printf("Selection: ");
        scanf("%d", &Options);
        printf("\n");

        if (Options == 1)
            searchPatientByPatientNumber(patient, max);
        else if (Options == 2)
            searchPatientByPhoneNumber(patient, max);

        clearInputBuffer();
        if (Options != 0)
            suspend();

    } while (Options != 0);
}

void addPatient(struct Patient patient[], int max)
{
    int i = 0, checkFreeElement = 1;

    // Iterates through all elements in patient
    while (checkFreeElement && i < max)
    {
        // Executes once and will only go through if there is an empty element
        if (patient[i].patientNumber == 0)
        {
            // User can now enter a new patient record
            patient[i].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[i]);

            checkFreeElement = 0;
        }

        i++;
    }

    if (checkFreeElement)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        printf("*** New patient record added ***\n\n");
    }

    return;
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNum, patientNumFound;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    patientNumFound = findIndexofpatientByPatientNum(patientNum, patient, max);

    if (patientNumFound != -1)
    {
        printf("\n");
        menuPatientEdit(&patient[patientNumFound]);
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }

    return;
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void removePatient(struct Patient patient[], int max)
{
    int patientnum, Index;
    char choice;
    printf("Enter the patient number: ");
    scanf("%d", &patientnum);

    // Checking if patient number exists
    if (findIndexofpatientByPatientNum(patientnum, patient, max) != -1)
    {
        Index = findIndexofpatientByPatientNum(patientnum, patient, max);
        printf("\nName  : %s\n", patient[Index].name);
        printf("Number: %05d\n", patient[Index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[Index].phone.number);
        printf(" (%s)\n\n", patient[Index].phone.description);

        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &choice);

        printf("ERROR: Character must be one of [yn]: ");
        scanf(" %c", &choice);
        scanf(" %c", &choice);
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N')
        {
            printf("Operation aborted.\n\n");
        }
        else
        {
            // Assigning patient to safe empty state so that the other function can't access it
            patient[Index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    clearInputBuffer();
}


// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data)
{
    int i, j;

    sortappointments(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->patients[j].patientNumber == data->appointments[i].patientNumber)
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }

    printf("\n");
    return;
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData *data)
{
    int i, j;
    int TOTALDAYS;
    struct Date searcheddate = {0};

    printf("Year        : ");
    searcheddate.year = inputIntPositive();

    printf("Month (1-12): ");
    searcheddate.month = inputIntRange(1, 12);

    TOTALDAYS = daysInMonth(searcheddate.year, searcheddate.month);

    printf("Day (1-%d)  : ", TOTALDAYS);
    searcheddate.day = inputIntRange(1, TOTALDAYS);
    printf("\n");

    sortappointments(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(&searcheddate, 0);

    // Prints out all the appointments that match with the date the user searched for
    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->patients[j].patientNumber == data->appointments[i].patientNumber)
            {
                if (searcheddate.year == data->appointments[i].date.year && searcheddate.month == data->appointments[i].date.month && searcheddate.day == data->appointments[i].date.day)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }

    printf("\n");
    return;
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment *appoints, int maxAppointments, struct Patient *patients, int maxPatient)
{
    struct Appointment searchedAppoint = {0};
    int TOTALDAYS, Indexofpatient, Appointmentvalidation, Indesofslot, slotavailable = 1;

    printf("Patient Number: ");
    searchedAppoint.patientNumber = inputIntPositive();
    Indexofpatient = findIndexofpatientByPatientNum(searchedAppoint.patientNumber, patients, maxPatient);

    // Checks if there is a spot for a new appointment
    Appointmentvalidation = isslotfilled(appoints, &Indesofslot, maxAppointments);

    // User enters their chosen appointment date and time
    if (!Appointmentvalidation)
    {
        // Checks if there is a valid patient ID
        if (Indexofpatient >= 0)
        {
            while (slotavailable)
            {
                printf("Year        : ");
                searchedAppoint.date.year = inputIntPositive();

                printf("Month (1-12): ");
                searchedAppoint.date.month = inputIntRange(1, 12);

                TOTALDAYS = daysInMonth(searchedAppoint.date.year, searchedAppoint.date.month);

                printf("Day (1-%d)  : ", TOTALDAYS);
                searchedAppoint.date.day = inputIntRange(1, TOTALDAYS);

                printf("Hour (0-23)  : ");
                searchedAppoint.time.hour = inputIntRange(0, 23);

                printf("Minute (0-59): ");
                searchedAppoint.time.min = inputIntRange(0, 59);

                // Checks if the chosen date is a valid date for a new appointment
                if (isAppointmentMatch(&searchedAppoint, appoints, maxAppointments))
                {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                }
                else
                {
                    validSchedule(&searchedAppoint);
                    slotavailable = 0;
                }
            }

            // The chosen appointment time slot is now registered
            appoints[Indesofslot].patientNumber = searchedAppoint.patientNumber;
            appoints[Indesofslot].date = searchedAppoint.date;
            appoints[Indesofslot].time = searchedAppoint.time;
            printf("\n*** Appointment scheduled! ***\n\n");
        }
        else
        {
            printf("\nERROR: Patient record not found!\n\n");
        }
    }
    else
    {
        printf("\nERROR: There are no more slots for an appointment!\n\n");
    }

    return;
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *appoints, int maxAppointments, struct Patient *patients, int maxPatient)
{
    struct Appointment searchedAppoint = {0};
    int TOTALDAYS, Indexofpatient, appointIndex = 0;

    printf("Patient Number: ");
    searchedAppoint.patientNumber = inputIntPositive();
    Indexofpatient = findIndexofpatientByPatientNum(searchedAppoint.patientNumber, patients, maxPatient);

    if (Indexofpatient >= 0)
    {
        printf("Year        : ");
        searchedAppoint.date.year = inputIntPositive();

        printf("Month (1-12): ");
        searchedAppoint.date.month = inputIntRange(1, 12);

        TOTALDAYS = daysInMonth(searchedAppoint.date.year, searchedAppoint.date.month);

        printf("Day (1-%d)  : ", TOTALDAYS);
        searchedAppoint.date.day = inputIntRange(1, TOTALDAYS);

        appointIndex = appointMatchIndex(&searchedAppoint, appoints, maxAppointments);

        if (appointIndex >= 0 && appointIndex < maxAppointments)
        {
            printf("\n");

            displayPatientData(&patients[Indexofpatient], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y')
            {
                appoints[appointIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
        }
        else
        {
            printf("ERROR: The appointment does not exist!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }

    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientnum, Index;
    printf("Search by patient number: ");
    scanf("%d", &patientnum);

    // Checking if patient number exists
    if (findIndexofpatientByPatientNum(patientnum, patient, max) != -1)
    {
        Index = findIndexofpatientByPatientNum(patientnum, patient, max);
        printf("\nName  : %s\n", patient[Index].name);
        printf("Number: %05d\n", patient[Index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[Index].phone.number);
        printf(" (%s)\n\n", patient[Index].phone.description);
    }

    else
    {
        printf("\n*** No records found ***\n\n");
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i = 0, tottalmatch = 0;
    char phoneNumber[PHONE_LEN + 1];
    clearInputBuffer();
    printf("Search by phone number: ");
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    printf("\n");
    displayPatientTableHeader();

    for (i = 0; i < max + 1; i++)
    {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0)
        {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            tottalmatch++;
        }
    }
    printf("\n");

    if (tottalmatch == 0)
    {
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int nextPatientNumber(const struct Patient patient[], int max)
{
    int nextNum, maxNum = patient[0].patientNumber, i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > maxNum)
        {
            maxNum = patient[i].patientNumber;
        }
    }

    nextNum = maxNum + 1;
    return nextNum;
}

// Find the patient array Index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int findIndexofpatientByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int founded, i = 0, flag = 1;

    while (flag && i < max)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            founded = i;
            flag = 0;
        }
        i++;
    }

    if (flag)
    {
        founded = -1;
    }

    return founded;
}

void sortappointments(struct Appointment *appoints, int max)
{
    int i, j;
    struct Appointment temp;

    for (i = 0; i < max; i++)
    {
        appoints[i].time.min =
            (appoints[i].date.year * 365 * 24 * 60) +
            ((int)((double)appoints[i].date.month / 12 * 365 * 24 * 60)) +
            (appoints[i].date.day * 24 * 60) +
            (appoints[i].time.hour * 60) +
            (appoints[i].time.min);
    }

    for (i = 0; i < max; i++)
    {
        for (j = 0; j < (max - 1 - i); j++)
        {
            if (appoints[j].time.min > appoints[j + 1].time.min)
            {
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < max; i++)
    {
        appoints[i].time.min =
            (appoints[i].time.min) -
            (appoints[i].date.year * 365 * 24 * 60) -
            ((int)((double)appoints[i].date.month / 12 * 365 * 24 * 60)) -
            (appoints[i].date.day * 24 * 60) -
            (appoints[i].time.hour * 60);
    }

    return;
}

int daysInMonth(const int year, const int month)
{
    int TOTALDAYS;

    if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
        TOTALDAYS = 30;
    }
    else if (month == 2)
    {
        // Leap year check
        if (((year % 4 == 0) && !(year % 100 == 0)) || (year % 400 == 0))
        {
            TOTALDAYS = 29;
        }
        else
        {
            TOTALDAYS = 28;
        }
    }
    else
    {
        TOTALDAYS = 31;
    }

    return TOTALDAYS;
}

int isAppointmentMatch(struct Appointment *searchAppoint, struct Appointment *appoints, int maxAppointments)
{
    int i, matchedappointment = 0;

    for (i = 0; i < maxAppointments; i++)
    {
        if (searchAppoint->date.year == appoints[i].date.year &&
            searchAppoint->date.month == appoints[i].date.month &&
            searchAppoint->date.day == appoints[i].date.day &&
            searchAppoint->time.hour == appoints[i].time.hour)
        {
            matchedappointment = 1;
        }
    }

    return matchedappointment;
}

int isslotfilled(const struct Appointment *appoints, int *appointSlotIndex, int maxAppointments)
{
    int valslot = 0, filled = 1;

    while (filled)
    {
        if (appoints[valslot].patientNumber < 1)
        {
            filled = 0;
        }
        valslot++;
    }

    *appointSlotIndex = valslot;

    return filled;
}

int appointMatchIndex(struct Appointment *searchAppoint, struct Appointment *appoints, int maxAppointments)
{
    int matchIndex = 0, notmatched = 1;

    while (notmatched && matchIndex < maxAppointments)
    {
        if (searchAppoint->patientNumber == appoints[matchIndex].patientNumber &&
            searchAppoint->date.year == appoints[matchIndex].date.year &&
            searchAppoint->date.month == appoints[matchIndex].date.month &&
            searchAppoint->date.day == appoints[matchIndex].date.day)
        {
            notmatched = 0;
        }
        matchIndex++;
    }
    matchIndex--;

    return matchIndex;
}

void validSchedule(struct Appointment *searchAppoint)
{
    while ((searchAppoint->time.hour < STARTING_HOUR) || (searchAppoint->time.hour > END_HOUR) ||
           (searchAppoint->time.min % INTERVAL != 0) ||
           (searchAppoint->time.hour >= END_HOUR && searchAppoint->time.min > 0))
    {

        printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", STARTING_HOUR, END_HOUR, INTERVAL);

        printf("Hour (0-23)  : ");
        searchAppoint->time.hour = inputIntRange(0, 23);

        printf("Minute (0-59): ");
        searchAppoint->time.min = inputIntRange(0, 59);
    }
    return;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: 0%4d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);

    printf("\n");
    inputPhoneData(&patient->phone);

    return;
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPhoneData(struct Phone *phone)
{
    int selection;

    printf("Phone Information\n-----------------\nHow will the patient like to be contacted?\n1. Cell\n");
    printf("2. Home\n3. Work\n4. TBD\nSelection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    default:
        break;
    }

    if (selection != 4)
    {
        printf("\nContact: %s", phone->description);
        printf("\nNumber : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
    }
    printf("\n");

    return;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char *datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;
    int Index = 0; // Number of patients.

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (!feof(fp) && Index < max)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[Index].patientNumber, patients[Index].name, patients[Index].phone.description, patients[Index].phone.number);

            if (!feof(fp))
            {
                Index++;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return Index;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char *datafile, struct Appointment appoints[], int max)
{
    FILE *fp = NULL;
    int Index = 0; // Number of appointments.

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (!feof(fp) && Index < max)
        {
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[Index].patientNumber, &appoints[Index].date.year, &appoints[Index].date.month, &appoints[Index].date.day, &appoints[Index].time.hour, &appoints[Index].time.min);

            if (!feof(fp))
            {
                Index++;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return Index;
}
