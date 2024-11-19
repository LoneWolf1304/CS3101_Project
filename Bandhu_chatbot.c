#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>


//Function to return the index of a substring in a string array
int indexOf(const char *str[], const char *substr, int size) {
    for (int i = 0; i < size; i++) {
        if (str[i] != NULL && substr != NULL && strcmp(str[i], substr) == 0) {
            return i;
        }
    }
    return -1;
}
//Function to convert a string to lowercase
char *lowering(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}
//Function to match the keywords  from the given response in the keywords array
const char *keyword_match(const char *keywords[], char *response, int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(response, keywords[i]) != NULL) {
            return keywords[i]; // Return the matched keyword
        }
    }
    return NULL; // No match found
}
//function to implement the keyword matching based chatbot
int chat(char *name) {
    char response[200];
    printw(">> ", name);
    getstr(response);

    // Ensure the response doesn't overflow
    response[sizeof(response) - 1] = '\0';

    // Convert response to lowercase
    lowering(response);

    // Defining the keyword arrays for specific purposes
    const char *greetingKeys[]={"hi", "hello", "good morning"};
    const char *flightBookingKeywords[] = {"book", "make", "make a booking", "book a flight"};
    const char *status_keys[] = {"status", "flight availability", "timing", "schedule", "arrival", "departure", "arrival time", "departure time", "flight delay", "delayed", "on time"};
    const char *cancellationKeywords[] = {"cancel", "cancellation", "cancelling", "refund", "refundable", "non-refundable", "cancel my booking", "cancel my flight"};
    const char *baggageKeywords[] = {"baggage", "baggage limit"};
    const char *paymentKeywords[] = {"payment methods", "payment methods available"};
    const char *mealKeywords[] = {"meal", "veg", "non-veg", "meal options"};
    const char *seatsKeywords[] = {"seats", "seat selection", "seat availability"};
    const char *refundKeywords[] = { "refund", "refund policy", "refunded", "refundable","get a refund"};

    // Matching the keywords for specific categories
    const char *result = keyword_match(flightBookingKeywords, response, sizeof(flightBookingKeywords) / sizeof(flightBookingKeywords[0]));
    const char *result1 = keyword_match(cancellationKeywords, response, sizeof(cancellationKeywords) / sizeof(cancellationKeywords[0]));
    const char *result2 = keyword_match(status_keys, response, sizeof(status_keys) / sizeof(status_keys[0]));
    const char *result3 = keyword_match(baggageKeywords, response, sizeof(baggageKeywords) / sizeof(baggageKeywords[0]));
    const char *result4 = keyword_match(paymentKeywords, response, sizeof(paymentKeywords) / sizeof(paymentKeywords[0]));
    const char *result5 = keyword_match(mealKeywords, response, sizeof(mealKeywords) / sizeof(mealKeywords[0]));
    const char *result6 = keyword_match(seatsKeywords, response, sizeof(seatsKeywords) / sizeof(seatsKeywords[0]));
    const char *result7 = keyword_match(refundKeywords, response, sizeof(refundKeywords) / sizeof(refundKeywords[0]));
    const char *result8 = keyword_match(greetingKeys, response, sizeof(greetingKeys) / sizeof(greetingKeys[0]));

    // Determining the category which pertains to the response
    const char *categories[] = {"book", "cancel", "status", "baggage", "payment", "meal", "seats", "refund", "hi"};
    const char *matches[] = {result, result1, result2, result3, result4, result5, result6, result7, result8};

    // Returning the index of the category
    for (int j = 0; j < 9; j++) {
        if (matches[j] != NULL) {
            return indexOf(categories, matches[j], 9);
        }
    }

    return -1; // No match
}

