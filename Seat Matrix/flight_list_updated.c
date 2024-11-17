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


void fileWrite()
{
    FILE *fptr;

    fptr = fopen("AirList.txt", "r");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);


    int i=0, cnt=0;
    flight air, *airs;
    int no_of_records = fileSize/sizeof(flight);
    airs = (flight*)malloc(no_of_records*sizeof(flight));

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
    {
        strcpy(airs[i].source, air.source);
        strcpy(airs[i].destination, air.destination);
        strcpy(airs[i].date, air.date);
        strcpy(airs[i].time, air.time);
        strcpy(airs[i].flightnum, air.flightnum);
        airs[i].seatsFree = air.seatsFree;
        airs[i].adult_price = air.adult_price;
        airs[i].child_price = air.child_price;
        airs[i].infant_price = air.infant_price;
        seat(air.flightnum, 60 );   
         i++;
    }
    fclose(fptr);


    // for(i = 0 ; i < no_of_records ; i++)
    // {
    //     fwrite(&totalflight[i], sizeof(flight), 1, fptr); 
    //     seat(totalflight[i].flightnum, 60 );       
    // }
    // fclose(fptr);


}
void main()
{
    fileWrite();
    //seat("AI202", 60);
}