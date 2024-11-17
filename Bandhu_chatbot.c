#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>

const char *flightBookingKeywords[] = {"book", "make"};
const char *status_keys[] = {"status", "flight availability", "timing", "schedule", "arrival", "departure", "arrival time", "departure time", "flight delay", "delayed", "on time"};
const char *cancellationKeywords[] = {"cancel", "cancellation", "cancelling", "refund", "refundable", "non-refundable"};
const char *baggageKeywords[] = {"baggage", "baggage limit"};
const char *paymentKeywords[] = {"payment", "methods", "charges"};
const char *mealKeywords[] = {"meal", "veg", "non-veg"};

char *lowering(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int indexOf(const char *str[], const char *substr, int size) {
    for (int i = 0; i < size; i++) {
        if (str[i] != NULL && substr != NULL && strcmp(str[i], substr) == 0) {
            return i;
        }
    }
    return -1;
}

const char *keyword_match(const char *key1[], char *key2[], int key1_size, int key2_size) {
    for (int i = 0; i < key2_size; i++) {
        for (int j = 0; j < key1_size; j++) {
            if (strcmp(key1[j], key2[i]) == 0) {
                return key1[0]; // Return the matched keyword
            }
        }
    }
    return NULL; // No match found
}

int chat(char *name) {
    char response[200];
    char *ptr;
    char *keywords[200];
    int i = 0;

    printw(">>", name);
    getstr(response);

    int len = strlen(response);
    if (len > 0 && response[len - 1] == '\n') {
        response[len - 1] = '\0'; // Remove newline
    }

    // Tokenize and store lowercase tokens in keywords
    ptr = strtok(response, " ");
    while (ptr != NULL) {
        keywords[i] = strdup(lowering(ptr)); // Duplicate and store token
        ptr = strtok(NULL, " ");
        i++;
    }

    // Match keywords
    const char *result = keyword_match(flightBookingKeywords, keywords, sizeof(flightBookingKeywords) / sizeof(flightBookingKeywords[0]), i);
    const char *result1 = keyword_match(cancellationKeywords, keywords, sizeof(cancellationKeywords) / sizeof(cancellationKeywords[0]), i);
    const char *result2 = keyword_match(status_keys, keywords, sizeof(status_keys) / sizeof(status_keys[0]), i);
    const char *result3 = keyword_match(baggageKeywords, keywords, sizeof(baggageKeywords) / sizeof(baggageKeywords[0]), i);
    const char *result5 = keyword_match(paymentKeywords, keywords, sizeof(paymentKeywords) / sizeof(paymentKeywords[0]), i);
    const char *result6 = keyword_match(mealKeywords, keywords, sizeof(mealKeywords) / sizeof(mealKeywords[0]), i);

    // Determine category
    const char *categories[] = {"book", "cancel", "status", "baggage", "payment", "meal"};
    const char *matches[] = {result, result1, result2, result3, result5, result6};

    for (int j = 0; j < 6; j++) {
        if (matches[j] != NULL) {
            // printf("Matched category: %s\n", matches[j]);
            // Cleanup allocated memory
            for (int k = 0; k < i; k++) {
                free(keywords[k]);
            }
            return indexOf(categories, matches[j], 6);
        }
    }

    // Cleanup allocated memory
    for (int k = 0; k < i; k++) {
        free(keywords[k]);
    }

    return -1; // No match
}

// int main() {
//     initscr();
//     printw("\nResult: %d", chat("Rahul"));
//     getch();
//     endwin();
//     return 0;
// }

