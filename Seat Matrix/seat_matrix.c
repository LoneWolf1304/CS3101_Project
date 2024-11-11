#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void seat(char flightnumb[], int seats) {
    FILE *fptr;
    char filename[20];  // Buffer to store the filename

    // Create a new filename by appending ".txt" to flightnumb without modifying it directly
    snprintf(filename, sizeof(filename), "%s.txt", flightnumb);

    // Open the file with the generated filename
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write a 10x6 matrix of random numbers to the file
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            // if(j!=3)
            // {
            // fprintf(fptr, "%d ", rand() % 2);
            // } 
            // else
            {
                // fprintf(fptr, " %d ", rand() % 2);
                fprintf(fptr, " %d ", 0);
            } // Add a space between numbers
        }
        fprintf(fptr, "\n");
    }

    // Close the file
    fclose(fptr);
}

// int main() {
//     seat("AI202", 60);
//     return 0;
// }
 

