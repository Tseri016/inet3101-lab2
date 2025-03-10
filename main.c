#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure definition
struct record {
    int partNumber;
    char partName[100];
    float partSize;
    char partSizeMetric[10];
    float partCost;
};

// Global variables
struct record *mainDB = NULL; // Pointer to the database
int num_records = 0;           // Number of records
int changeCounter = 0;         // Tracks the number of modifications
char dataName[20];             // Database name

// Function prototypes
void addRecord(void);
void deleteRecord();
void printAllRecords();
void printNumRecords();
void printDatabaseSize();
void printNumChanges(bool print);
void menu();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\nError: No Database name provided!\n\n");
        return 1;
    }

    strcpy(dataName, argv[1]);
    menu();
    return 0;
}

// Function to add a new record
void addRecord() {
    num_records++;
    struct record *tempDB = (struct record *)malloc(num_records * sizeof(struct record));

    if (tempDB == NULL) {
        printf("\nMemory allocation failed!\n");
        num_records--;
        return;
    }

    // Copy existing records to new memory
    for (int i = 0; i < num_records - 1; i++) {
        tempDB[i] = mainDB[i];
    }

    // Get new record input
    printf("\nEnter Part Number: ");
    scanf("%d", &tempDB[num_records - 1].partNumber);
    
    printf("Enter Part Name: ");
    scanf("%s", tempDB[num_records - 1].partName);

    printf("Enter Part Size: ");
    scanf("%f", &tempDB[num_records - 1].partSize);

    printf("Enter Part Size Metric: ");
    scanf("%s", tempDB[num_records - 1].partSizeMetric);

    printf("Enter Part Cost: ");
    scanf("%f", &tempDB[num_records - 1].partCost);

    // Free old memory and assign new memory
    free(mainDB);
    mainDB = tempDB;
    changeCounter++;

    printf("\nRecord added successfully!\n\n");
}

// Function to delete the last record
void deleteRecord() {
    if (num_records == 0) {
        printf("\nNo records to delete.\n\n");
        return;
    }

    num_records--;
    struct record *tempDB = (struct record *)malloc(num_records * sizeof(struct record));

    if (tempDB == NULL && num_records > 0) {
        printf("\nMemory allocation failed!\n");
        num_records++;
        return;
    }

    // Copy existing records to new memory (excluding last one)
    for (int i = 0; i < num_records; i++) {
        tempDB[i] = mainDB[i];
    }

    // Free old memory and assign new memory
    free(mainDB);
    mainDB = tempDB;
    changeCounter++;

    printf("\nLast record deleted successfully!\n\n");
}

// Function to print all records
void printAllRecords() {
    if (num_records == 0) {
        printf("\nNo records available.\n\n");
        return;
    }

    for (int i = 0; i < num_records; i++) {
        printf("\nRecord %d:\n", i + 1);
        printf("Part Number: %d\n", mainDB[i].partNumber);
        printf("Part Name: %s\n", mainDB[i].partName);
        printf("Part Size: %.2f %s\n", mainDB[i].partSize, mainDB[i].partSizeMetric);
        printf("Part Cost: $%.2f\n", mainDB[i].partCost);
    }
    printf("\n");
}

// Function to print the number of records
void printNumRecords() {
    printf("\nNumber of records in %s database: %d\n\n", dataName, num_records);
}

// Function to print database size
void printDatabaseSize() {
    printf("\nDatabase size: %lu bytes\n\n", num_records * sizeof(struct record));
}

// Function to print the number of changes
void printNumChanges(bool print) {
    if (print) {
        printf("\nDatabase %s has been accessed %d times.\n\n", dataName, changeCounter);
    } else {
        changeCounter++;
    }
}

// Menu function
void menu() {
    int choice;
    bool running = true;

    while (running) {
        printf("\nMENU\n");
        printf("1. Print all records\n");
        printf("2. Add record\n");
        printf("3. Delete last record\n");
        printf("4. Print number of records\n");
        printf("5. Print database size\n");
        printf("6. Print number of accesses\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printAllRecords();
                break;
            case 2:
                addRecord();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                printNumRecords();
                break;
            case 5:
                printDatabaseSize();
                break;
            case 6:
                printNumChanges(true);
                break;
            case 7:
                printf("\nExiting...\n");
                running = false;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    // Free allocated memory before exiting
    free(mainDB);
}
