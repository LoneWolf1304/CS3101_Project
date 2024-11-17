//Reading/writing structure-wise (fixed-length record)

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "seat_matrix.c"
typedef struct {
	char flightnum[50];
	int seatsFree;
	char source[100];
	char destination [100];
	char date[50]; 
    char time[50];
} flight;

flight totalflight[50]=
{   {"AI202", 60, "Kolkata", "Delhi", "12-04-2024", "18:00"},
    {"IGO1013", 60, "Bengaluru", "Madurai", "12-04-2024", "18:00"},
    {"SEJ1081", 60, "Chennai","Mumbai","12-04-2024", "18:00"},
    {"AI982", 60, "Hyderabad", "Cochin", "12-04-2024" , "18:00"},
    {"IGO1013", 60, "Delhi", "Singapore", "12-04-2024", "18:00"},
    {"IGO1115", 60, "Bengaluru", "Phuket", "12-04-2024"},
    {"SEJ1035", 60, "Guwahati","Kolkata","12-04-2024", "18:00"},
    {"IGO1235", 60, "Hyderabad", "Ahmedabad", "12-04-2024" , "18:00"}

    
};

void fileWrite(int no_of_records)
{
    FILE *fptr;
    int i;

    fptr = fopen("./Seat Matrix/AirList.txt", "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < no_of_records ; i++)
    {
        fwrite(&totalflight[i], sizeof(flight), 1, fptr); 
        seat(totalflight[i].flightnum, 60 );       
    }
    fclose(fptr);


}
void main()
{
    fileWrite(sizeof(totalflight)/sizeof(flight));
    //seat("AI202", 60);
}