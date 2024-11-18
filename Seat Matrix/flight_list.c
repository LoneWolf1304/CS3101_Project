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
    double adult_price;
    double child_price;
    double infant_price;
} flight;

flight totalflight[50]=
{   {"AI202", 60, "Kolkata", "Delhi", "11-04-2024", "18:00", 5100.0, 3000.0, 0.0},
    {"IGO1013", 60, "Bengaluru", "Madurai", "13-09-2024", "18:00",5200.0, 3200.0, 0.0},
    {"SEJ1081", 60, "Chennai","Mumbai","18-06-2024", "18:00" ,5300.0, 3400.0, 0.0},
    {"AI982", 60, "Hyderabad", "Cochin", "12-10-2024" , "18:00",5400.0, 3600.0, 0.0},
    {"IGO1013", 60, "Delhi", "Singapore", "17-12-2024", "18:00",5500.0, 3800.0, 0.0},
    {"IGO1115", 60, "Bengaluru", "Phuket", "19-05-2024","18:00",5600.0, 3100.0, 0.0},
    {"SEJ1035", 60, "Guwahati","Kolkata","01-03-2024", "18:00",5700.0, 3500.0, 0.0},
    {"IGO1235", 60, "Hyderabad", "Ahmedabad", "21-08-2024" , "18:00",5800.0, 3900.0, 0.0}

    
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
        seat(totalflight[i].flightnum, 60 );       
    }
    fclose(fptr);


}
void main()
{
    fileWrite(sizeof(totalflight)/sizeof(flight));
    //seat("AI202", 60);
}