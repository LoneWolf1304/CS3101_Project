#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#define MAX_FlIGHTS=50
#define MAX_SEATS-60

typedef struct {
	int flightnum;
	int seatsFree;
	int source[100];
	int destination [100];
	char date[11]; 
} flight;

typedef struct {

	char name[100];
	int flightnum;

} booking;

flight totalflight[MAX_FLIGHTS];    // array of structures


void searchFlight(const char* source, const char* destination, const char* date){  //function to searchFlights
	clear();
	int flag=0;
//	printw("Avilabale Flight from %s to %s on %s:\n",source,destination,date);
	printw("Please Wait....");
	for (int i =0; i < MAX_FLIGHTS; i++){
		if (strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0 ){
		
		printw("Flight Available !\n");
		printw("Flight Number: %d, Seats Available: %d\n",totalflight[i].flightnum,flight[i].seatsFree);
		flag++;
		}
	}
	if(flag==0){

		printw("Soor ! No flights found");
	}
	
	printw("Press any key to continue!");


}


int bookFlight(int flightnum ){
	for(int i=0;i< MAX_FLIGHTS;i++){

		if(totalflight[i].flightnum=flightnum){
			
			if(totalflight[i].seatsFree>0){
				totalflight[i].seatsFree--;
				printw("Booking Sucessful !");
				return 1;
			}
			else
				printw("Sorry ! No seats Available :(");
				return 0;

		}
	}

	printw("No flights found!");

}






	
