#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "address_book.h"
#include <time.h>
#include "validation.h"

#define MAX_LINE_SIZE 1024 
char fileName[100];

void modifyEntry(FILE *file, const char *fileName) {

    printf("Existing entries:\n");
    int index = 1;
    struct AddressBookEntry entry;
    rewind(file);

    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        printf("%d. %s %s\n", index, entry.name, entry.lastName);
        index++;
    }

    int entryNumber;
    printf("\nEnter the index of the entry you want to modify: ");
    scanf("%d", &entryNumber);

    rewind(file);

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        exit(EXIT_FAILURE);
    }

    bool found = false;
    int num;
    int currentEntry = 1;


    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        if (currentEntry == entryNumber) {
            found = true;
            // Modify selected entry
            printf("Modify entry:\n");
            printf("Select the field you want to modify:\n");
            printf("1. Name\n");
            printf("2. Last Name\n");
            printf("3. Weight\n");
            printf("4. Date\n");
            printf("5. Email\n");
            printf("6. Phone Number\n");
            printf("Enter your choice: ");
            int fieldChoice;
            scanf("%d", &fieldChoice);

            switch (fieldChoice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", entry.name);
                    while (!validateString(entry.name)) {
                        printf("Invalid name format. Enter a name with only letters: ");
                        scanf("%s", entry.name);
                    }
                    break;
                case 2:
                    printf("Enter new last name: ");
                    scanf("%s", entry.lastName);
                    while (!validateString(entry.lastName)) {
                        printf("Invalid last name format. Enter a last name with only letters: ");
                        scanf("%s", entry.lastName);
                    }
                    break;
                case 3:
                    printf("Enter new weight (Integer): ");
                    scanf("%d", &entry.weight);
                    while (!validateWeight(entry.weight)) {
                        printf("Invalid weight format. Enter a last name with only non-negative digits: ");
                        scanf("%s", entry.weight);
                    }
                    break;
                case 4:
                     

                    while (1) {
                        printf("To use current date Press 1:\n");
                        printf("To enter old date Press 2:\n");
                        printf("Enter your choice: ");
                        scanf("%d", &num); 

                        if (num == 2) {
                            printf("Enter the old date (DD-MM-YYYY): ");
                            scanf("%s",entry.date);
                        } else if (num == 1) {
                            time_t currentTime;
                            time(&currentTime);
                            struct tm *localTime = localtime(&currentTime);
                            sprintf(entry.date, "%02d-%02d-%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
                        } else {
                            printf("Invalid choice. Please try again: ");
                            continue; 
                        }

                        if (!validateDate(entry.date)) {
                            printf("Invalid date format. Enter a valid date (DD-MM-YYYY): ");
                            continue; 
                        }

                        break;
                    }
                case 5:
                    printf("Enter new email: ");
                    scanf("%s", entry.email);
                    while (!validateEmail(entry.email)) {
                        printf("Invalid email format. Enter a valid email: ");
                        scanf("%s", entry.email);
                    }
                    break;
                case 6:
                    printf("Enter new phone number: ");
                    scanf("%s", entry.phoneNumber);
                    while (!validatePhoneNumber(entry.phoneNumber)) {
                        printf("Invalid phone number format. Enter a valid phone number: ");
                        scanf("%s", entry.phoneNumber);
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
            
            // Check if any field is empty
            if (strlen(entry.name) == 0 || strlen(entry.lastName) == 0 || entry.weight <= 0 || strlen(entry.date) == 0 ||
                strlen(entry.email) == 0 || strlen(entry.phoneNumber) == 0) {
                printf("Error: All fields are required. Please fill in all the fields.\n");
                fclose(tempFile);
                remove("temp.csv");
                return;
            }
        }
        fprintf(tempFile, "%s,%s,%d,%s,%s,%s\n", entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
        currentEntry++;
    }

    if (!found) {
        printf("Invalid entry index. No entry found with the specified index.\n");
        fclose(file);
        fclose(tempFile);
        remove("temp.csv");
        return;
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName); 
    rename("temp.csv", fileName); 
    FILE *file1;
    file1 = fopen(fileName, "a+");    
    printf("Entry modified successfully!\n");
}

void saveNewEntry(FILE *file) {
    struct AddressBookEntry newEntry;
    int option;

    printf("\nEnter details for the new entry:\n");
    printf("1. Add new entry\n");
    printf("2. Modify existing entry\n");
    printf("3. Delete existing entry\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    if (option == 1) {
        printf("Name: ");
        scanf("%s", newEntry.name);
        while (!validateString(newEntry.name)) {
            printf("Invalid name format. Enter a name with only letters: ");
            scanf("%s", newEntry.name);
        }

        printf("Last Name: ");
        scanf("%s", newEntry.lastName);
        while (!validateString(newEntry.lastName)) {
            printf("Invalid last name format. Enter a last name with only letters: ");
            scanf("%s", newEntry.lastName);
        }
        
        printf("Weight (Integer): ");
        scanf("%d", &newEntry.weight);
        while (!validateWeight(newEntry.weight)) {
            printf("Invalid weight format. Enter a last name with only non-negative digits: ");
            scanf("%s", newEntry.weight);
        }
        

        int num; // Declare num variable.

        while (1) {
            printf("To use current date Press 1:\n");
            printf("To enter old date Press 2:\n");
            printf("Enter your choice: ");
            scanf("%d", &num); 

            if (num == 2) {
                printf("Enter the old date (DD-MM-YYYY): ");
                scanf("%s", newEntry.date);
            } else if (num == 1) {
                time_t currentTime;
                time(&currentTime);
                struct tm *localTime = localtime(&currentTime);
                sprintf(newEntry.date, "%02d-%02d-%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
            } else {
                printf("Invalid choice. Please try again: ");
                continue; 
            }

            if (!validateDate(newEntry.date)) {
                printf("Invalid date format. Enter a valid date (DD-MM-YYYY): ");
                continue; 
            }

            break;
        }

        printf("Email: ");
        scanf("%s", newEntry.email);
        while (!validateEmail(newEntry.email)) {
            printf("Invalid email format. Enter a valid email: ");
            scanf("%s", newEntry.email);
        }

        printf("Phone Number: ");
        scanf("%s", newEntry.phoneNumber);
        while (!validatePhoneNumber(newEntry.phoneNumber)) {
            printf("Invalid phone number format. Enter a valid phone number: ");
            scanf("%s", newEntry.phoneNumber);
        }

        if (strlen(newEntry.name) == 0 || strlen(newEntry.lastName) == 0 || newEntry.weight <= 0 || strlen(newEntry.date) == 0 ||
            strlen(newEntry.email) == 0 || strlen(newEntry.phoneNumber) == 0) {
            printf("Error: All fields are required. Please fill in all the fields.\n");
            return;
        }

        fprintf(file, "%s,%s,%d,%s,%s,%s\n", newEntry.name, newEntry.lastName, newEntry.weight, newEntry.date, newEntry.email, newEntry.phoneNumber);
        printf("New entry added successfully!\n");

    } else if (option == 2) {  
        modifyEntry(file, fileName);
    } else if (option == 3) {
        deleteEntry(file);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

void retrieveInformation(FILE *file) {
    int choice;
    printf("\nHow would you like to search for the data?\n");
    printf("1. Display filtered information\n");
    printf("2. Display all information\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    struct AddressBookEntry entry; // Declare outside the switch statement

    switch(choice) {
        case 1:
        {
            char field[50];
            char criteria[50];

            printf("Enter the field for retrieval (e.g., name, lastName, weight, date, email, phoneNumber): ");
            scanf("%s", field);
            printf("Enter the criteria for %s: ", field);
            scanf("%s", criteria);

            rewind(file);

            int found = 0;
            int entryIndex = 0;
            struct AddressBookEntry matchingEntries[100]; // Max 100 entries for simplicity

            while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
                if ((strcmp(field, "name") == 0 && strcmp(entry.name, criteria) == 0) ||
                    (strcmp(field, "lastName") == 0 && strcmp(entry.lastName, criteria) == 0) ||
                    (strcmp(field, "weight") == 0 && entry.weight == atoi(criteria)) ||
                    (strcmp(field, "date") == 0 && strcmp(entry.date, criteria) == 0) ||
                    (strcmp(field, "email") == 0 && strcmp(entry.email, criteria) == 0) ||
                    (strcmp(field, "phoneNumber") == 0 && strcmp(entry.phoneNumber, criteria) == 0)) {

                    found = 1;
                    printf("%d. Name: %s, Last Name: %s, Date: %s\n", entryIndex + 1, entry.name, entry.lastName, entry.date);
                    matchingEntries[entryIndex] = entry;
                    entryIndex++;
                }
            }

            if (!found) {
                printf("No matching entry found for the specified criteria.\n");
            } else {
                printf("Enter the index of the entry you want to view: ");
                int selectedIndex;
                scanf("%d", &selectedIndex);

                if (selectedIndex > 0 && selectedIndex <= entryIndex) {
                    printf("---------------\n");
                    struct AddressBookEntry selectedEntry = matchingEntries[selectedIndex - 1];
                    printf("Name: %s\n", selectedEntry.name);
                    printf("Last Name: %s\n", selectedEntry.lastName);
                    printf("Weight: %d\n", selectedEntry.weight);
                    printf("Date: %s\n", selectedEntry.date);
                    printf("Email: %s\n", selectedEntry.email);
                    printf("Phone Number: %s\n", selectedEntry.phoneNumber);
                } else {
                    printf("Invalid index selected.\n");
                }
            }
            break;
        }

        case 2:
            rewind(file);
            while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
                printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                    entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                printf("-------------------------\n");
            }
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

void deleteEntry(FILE *file) {
    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        exit(EXIT_FAILURE);
    }

    int index = 1;
    int entryNumber;
    printf("Existing entries:\n");
    struct AddressBookEntry entry;

    rewind(file);
    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        printf("%d. %s %s\n", index, entry.name, entry.lastName);
        index++;
    }

    printf("\nEnter the index of the entry you want to delete: ");
    scanf("%d", &entryNumber);

    rewind(file);
    int currentEntry = 1;
    bool found = false;

    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        if (currentEntry != entryNumber) {
            fprintf(tempFile, "%s,%s,%d,%s,%s,%s\n", entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
        } else {
            found = true;
        }
        currentEntry++;
    }

    if (!found) {
        printf("Invalid entry index. No entry found with the specified index.\n");
    } else {
        printf("Entry deleted successfully!\n");
    }

    fclose(file);
    fclose(tempFile);
    remove(fileName); 
    rename("temp.csv", fileName); 
    FILE *file2;
    file2 = fopen("fileName", "a+");    
}
