#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>


#define MAX_FLIGHTS 50
#define MAX_SEATS 60

typedef struct {
	int flightnum;
	int seatsFree;
	char source[100];
	char destination [100];
	char date[11]; 
} flight;

typedef struct {

	char name[100];
	int flightnum;

} booking;

flight totalflight[MAX_FLIGHTS];    // array of structures


void searchFlight(const char* source, const char* destination, const char* date){  //function to searchFlights

	printw("Avilabale Flight from %s to %s on %s:\n",source,destination,date);
	for (int i =0; i < MAX_FLIGHTS; i++){
		if (strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0 ){

		printw("Flight Available !\n");
		printw("Flight Number: %d, Seats Available: %d\n",totalflight[i].flightnum,totalflight[i].seatsFree);

		}
	}


}


int bookFlight(int flightnum){

	int numTicket;

	for(int i=0; i< MAX_FLIGHTS;i++){
		if(totalflight[i].flightnum=flightnum){
			printw("The number of seats avaiable: %d",totalflight[i].seatsFree);
			printw("Enter number of seats to be booked:");
			echo();
			scanw("%d",&numTicket);
			noecho();
			if(numTicket >0 && numTicket <= totalflight[i].seatsFree){

				totalflight[i].seatsFree=totalflight[i].seatsFree-numTicket;
				printw("Booked Sucessfully !!");
				return 1;
			}
			else{

				printw("Invalid Request :(");
			return 0;
			}
		}
	}
	printw("Flight not found");
	return 0;
}








	
