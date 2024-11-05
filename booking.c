#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include "airplane_list.h"

#define MAX_FLIGHTS 50
#define MAX_SEATS 60



typedef struct {

	char name[100];
	char flightnum[50];

} booking;
   // array of structures
int size = sizeof(totalflight)/sizeof(flight);



void searchFlight(char* source,  char* destination,  char* date){  //function to searchFlights
	int flag=0;
	printw("Available Flight from %s to %s on %s:\n",source,destination,date);
	for (int i =0; i < size; i++){
		if (strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0 ){

		printw("Flight Available !\n");
		printw("Flight Number: %s, Seats Available: %d\n",totalflight[i].flightnum,totalflight[i].seatsFree);
		flag++;
		}
	}
	if(flag==0){
		int rowc, colc;
    	getmaxyx(stdscr,rowc,colc);
		const char *art[] = {
        "      .-\"\"\"\"\"-.    ",
        "   .'          '.   ",
        "  /   O      O   \\  ",
        ":           `    :",
        "|                 |   ",
        ":    .------.    :",
        " \\  '        '   / ",
        "  '.           .'  ",
        "     '-......-'    "
    	};

    // Get the number of rows in the ASCII art
    int numRows = sizeof(art) / sizeof(art[0]);

    // Print the art to the screen
    for (int i =0 ; i < numRows; i++) {
		move((rowc/2)-10+i, colc/2);
        printw("%s", art[i]);
    }
	move((rowc/2)-8+numRows, (colc/2));
	printw("Sorry ! No flights found\n");
	move((rowc/2)-10+numRows+4, (colc/2));
	printw("Press any key to continue!");
	}


}


int bookFlight(char* flightnum){

	int numTicket;

	for(int i=0; i< size;i++){
		if(strcmp(totalflight[i].flightnum, flightnum)==0){
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
	int rowc, colc;
    	getmaxyx(stdscr,rowc,colc);
		const char *art[] = {
        "      .-\"\"\"\"\"-.    ",
        "   .'          '.   ",
        "  /   O      O   \\  ",
        ":           `    :",
        "|                 |   ",
        ":    .------.    :",
        " \\  '        '   / ",
        "  '.           .'  ",
        "     '-......-'    "
    	};

    // Get the number of rows in the ASCII art
    int numRows = sizeof(art) / sizeof(art[0]);

    // Print the art to the screen
    for (int i =0 ; i < numRows; i++) {
		move((rowc/2)-10+i, colc/2);
        printw("%s", art[i]);
    }
	move((rowc/2)-8+numRows, (colc/2));
	printw("Flight not found");
	return 0;
}








	
