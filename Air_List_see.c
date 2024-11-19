#include<stdio.h>
#include<stdlib.h>


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

void main()
{
    FILE *fptr;
    flight air;
    fptr = fopen("./Seat Matrix/AirList.txt", "r");
    while(fread(&air, sizeof(flight), 1, fptr)) 
    {
        printf("%s %d %s %s %s %s %lf %lf %lf\n", air.flightnum, air.seatsFree, air.source, air.destination, air.date, air.time, air.adult_price, air.child_price, air.infant_price);
    }
    fclose(fptr);
}