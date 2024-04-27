#include <stdio.h>
#include "validation.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validateString(const char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

bool validateEmail(const char *email) {
    int at_count = 0;
    int dot_count = 0;
    int length = strlen(email);
    
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            at_count++;
        } else if (email[i] == '.') {
            dot_count++;
        }
    }
    
    return at_count == 1 && dot_count >= 1;
}

bool validateDate(const char *date) {
    int length = strlen(date);

    if (length != 10) { // Check length for dd-mm-yyyy format
        return false;
    }

    // Validate the format (dd-mm-yyyy)
    if (date[2] != '-' || date[5] != '-') {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (i == 2 || i == 5) {
            continue; // Skip dashes
        }
        if (!isdigit(date[i])) {
            return false;
        }
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    // Validate day, month, and year ranges
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2025) {
        return false;
    }

    return true;
}


bool validatePhoneNumber(const char *phoneNumber) {
    int digit_count = 0;
    int length = strlen(phoneNumber);
    
    for (int i = 0; i < length; i++) {
        if (isdigit(phoneNumber[i])) {
            digit_count++;
        }
    }

    for (int i = 0; i < length; i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    
    return digit_count >= 7; 
}

bool validateWeight(int weight) {
    return weight >= 0; 
}

