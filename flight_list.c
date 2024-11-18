#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
	char flightnum[50];
	int seatsFree;
	char source[100];
	char destination [100];
	char date[50]; 
    char time[50];
    char type;
    double price;
} flight;

flight totalflight[50]=
{   {"AI202", 15, "Kolkata", "Delhi", "12-04-2024", "18:00"},
    {"IGO1013", 23, "Bengaluru", "Madurai", "12-04-2024", "18:00"},
    {"SEJ1081", 15, "Chennai","Mumbai","12-04-2024", "18:00"},
    {"AI982", 30, "Hyderabad", "Cochin", "12-04-2024" , "18:00"},
    {"IGO1013", 15, "Delhi", "Singapore", "12-04-2024", "18:00"},
    {"IGO1115", 23, "Bengaluru", "Phuket", "12-04-2024"},
    {"SEJ1035", 15, "Guwahati","Kolkata","12-04-2024", "18:00"},
    {"IGO1235", 30, "Hyderabad", "Ahmedabad", "12-04-2024" , "18:00"}

    
};

void fileWrite(int no_of_records)
{
    FILE *fptr;
    int i;

    fptr = fopen("AirList.txt", "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < no_of_records ; i++)
    {
        fwrite(&totalflight[i], sizeof(flight), 1, fptr);        
    }
    fclose(fptr);


}
void main()
{
    fileWrite(sizeof(totalflight)/sizeof(flight));
}