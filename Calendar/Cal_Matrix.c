#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void cal(int days, char *month) 
{
    FILE *fptr;
    char filename[100];  // Buffer to store the filename

    // Create a new filename by appending ".txt" to flightnumb without modifying it directly
    snprintf(filename, sizeof(filename), "/home/shaggy1304/IISER/Lab_Files/CS/CS3101_Project/Calendar/%s.txt", month);

    // Open the file with the generated filename
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write a 10x6 matrix of random numbers to the file
    int a=1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) 
        {
            if(a>days)
            {
                fprintf(fptr, " %d ", 0);
            }
            else
            {
                // fprintf(fptr, " %d ", rand() % 2);
                fprintf(fptr, " %d ", a);
                a++;
            } // Add a space between numbers
        }
        fprintf(fptr, "\n");
    }

    // Close the file
    fclose(fptr);
}
void main()
{
    cal(31,"january");
    cal(28,"february");
    cal(31,"march");
    cal(30,"april");
    cal(31,"may");
    cal(30,"june");
    cal(31,"july");
    cal(31,"august");
    cal(30,"september");
    cal(31,"october");
    cal(30,"november");
    cal(31,"december");
}