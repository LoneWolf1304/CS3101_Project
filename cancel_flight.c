#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include "airplane_list.h"

#define MAX_FLIGHTS 50
#define MAX_SEATS 60
#define MAX_BOOKINGS 50



int cancelFlight(char* flightnum){
    FILE *fptr;
    flight air, *airs;
    int no_of_rec = 0, i;

    fptr = fopen("AirList.txt", "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&air, sizeof(flight), 1, fptr)) 
    {
        
        
        no_of_rec++;//count the number of records (each record is a air type variable)

    }
    airs = (flight*)malloc(no_of_rec*sizeof(flight));
    rewind(fptr);

    i=0;
    while(fread(&air, sizeof(flight), 1, fptr))
    {
        
        strcpy(airs[i].source, air.source);
        strcpy(airs[i].destination, air.destination);
        strcpy(airs[i].date, air.date);
        strcpy(airs[i].time, air.time);
        strcpy(airs[i].flightnum, air.flightnum);
        airs[i].seatsFree = air.seatsFree;
        i++;
        

    }
    fclose(fptr);

    for(int i=0; i<no_of_rec; i++){
        if(strcmp(airs[i].flightnum, flightnum)==0){
            printw("The number of seats avaiable: %d\n",airs[i].seatsFree);
            printw("Enter number of seats to be cancelled:");
            int numTicket;
            scanw("%d",&numTicket);
            if(numTicket >0){
                airs[i].seatsFree=airs[i].seatsFree+numTicket;
                printw("%d seats Cancelled Sucessfully !!",numTicket);

                fptr = fopen("AirList.txt", "w");
                if (fptr == NULL)
                {
                    printf("Error opening file!\n");
                    free(airs);
                    exit(1);
                }
                
                for(i = 0 ; i < no_of_rec ; i++)
                {
                    fwrite(&airs[i], sizeof(flight), 1, fptr);      
                }
                fclose(fptr);
                free(airs);
                return 1;

                
            }else{
                printw("Invalid Cancellation Request :(");
                free(airs);
                return 0;
            }
        }
    }
    printw("Flight not found");
    return 0;
}

