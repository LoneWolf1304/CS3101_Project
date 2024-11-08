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
//int size = sizeof(totalflight)/sizeof(flight);

void fileReadWrite(char* filename, char* airnum, int seats)

{
    FILE *fptr;
    flight air, *airs;
    int no_of_rec = 0, i;


    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&air, sizeof(flight), 1, fptr)) 
    {
        
        
        no_of_rec++;//count the number of records (each record is a air type variable)

    }
    
    airs = (flight*)malloc(no_of_rec*sizeof(flight));//allocating dynamically space for the number of records in the file to be read
    
    rewind(fptr);//going to the beginning of the file
    
    i = 0;

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
    {
        //printf("Current position: %ld  ", ftell(fptr));
        //printf ("Title = %s id = %s stock = %d\n", air.title, 
        //air.id, air.no); 
        
        strcpy(airs[i].source, air.source);
		strcpy(airs[i].destination, air.destination);
		strcpy(airs[i].date, air.date);
		strcpy(airs[i].time, air.time);
		strcpy(airs[i].flightnum, air.flightnum);
    	airs[i].seatsFree = air.seatsFree;
    	if(strcmp(air.flightnum, airnum) == 0)//check if this is the record to be updated
        {
        	airs[i].seatsFree -=seats;//updating
		}
    	
    	i++;
    }  

    fclose(fptr);
    
    //printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < no_of_rec ; i++)
    {
        fwrite(&airs[i], sizeof(flight), 1, fptr); //overwriting the file with the updated record (even the unchanged records are overwritten)       
    }
    
    fclose(fptr);
}





void searchFlight(char* source,  char* destination,  char* date, char* tim){
	
	FILE *fptr;
    flight air;
	flight *totalflight;
    int no_of_rec = 0, i;
    fptr = fopen("AirList.txt", "r");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&air, sizeof(flight), 1, fptr)) 
    {
        
        
        no_of_rec++;//count the number of records (each record is a air type variable)

    }
    
   totalflight = (flight*)malloc(no_of_rec*sizeof(flight));//allocating dynamically space for the number of records in the file to be read
    
    rewind(fptr);//going to the beginning of the file
    i = 0;

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
    {
        //printf("Current position: %ld  ", ftell(fptr));
        //printf ("Title = %s id = %s stock = %d\n", air.title, 
        //air.id, air.no); 
        
        strcpy(totalflight[i].source, air.source);
		strcpy(totalflight[i].destination, air.destination);
		strcpy(totalflight[i].date, air.date);
		strcpy(totalflight[i].time, air.time);
		strcpy(totalflight[i].flightnum, air.flightnum);
    	totalflight[i].seatsFree = air.seatsFree;
    	i++;
    }  

    fclose(fptr);
	int size = no_of_rec;
	  //function to search flights
	int flag=0;
	printw("Available flight from %s to %s on %s:\n",source,destination,date);
	for (int i =0; i < size; i++){
		if (strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0 && strcmp(totalflight[i].time,tim) == 0){

		//printw("Flight Available !\n");
		printw("Flight Number: %s, Seats Available: %d\n",totalflight[i].flightnum,totalflight[i].seatsFree);
		flag++;
		}
	}
	if(flag==0){
		int rowc, colc;
    	getmaxyx(stdscr,rowc,colc);
		int numRows=0;
		// const char *art[] = {
        // "      .-\"\"\"\"\"-.    ",
        // "   .'          '.   ",
        // "  /   O      O   \\  ",
        // ":           `    :",
        // "|                 |   ",
        // ":    .------.    :",
        // " \\  '        '   / ",
        // "  '.           .'  ",
        // "     '-......-'    "
    	// };

    // Get the number of rows in the ASCII art
    // int numRows = sizeof(art) / sizeof(art[0]);

    // // Print the art to the screen
    // for (int i =0 ; i < numRows; i++) {
	// 	move((rowc/2)-10+i, colc/2);
    //     printw("%s", art[i]);
    // }
	move((rowc/2)-8+numRows, (colc/2));
	printw("Sorry ! No flights found\n");
	move((rowc/2)-10+numRows+4, (colc/2));
	printw("Press any key to continue!");
	}


}
typedef struct {
	char name[50];
	int age;
	char gender[10];
} BOOKER;

int bookFlight(char* flightnum){

FILE *fptr;
    flight air, *airs;
    int no_of_rec = 0, i;
	flight *totalflight;

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
    
    totalflight = (flight*)malloc(no_of_rec*sizeof(flight));//allocating dynamically space for the number of records in the file to be read
    
    rewind(fptr);//going to the beginning of the file
    i = 0;

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
    {
        //printf("Current position: %ld  ", ftell(fptr));
        //printf ("Title = %s id = %s stock = %d\n", air.title, 
        //air.id, air.no); 
        
        strcpy(totalflight[i].source, air.source);
		strcpy(totalflight[i].destination, air.destination);
		strcpy(totalflight[i].date, air.date);
		strcpy(totalflight[i].time, air.time);
		strcpy(totalflight[i].flightnum, air.flightnum);
    	totalflight[i].seatsFree = air.seatsFree;
    	i++;
    }  

    fclose(fptr);

	int size = no_of_rec;

	int numTicket;

	for(int i=0; i< size;i++){
		if(strcmp(totalflight[i].flightnum, flightnum)==0){
			printw("The number of seats avaiable: %d\n",totalflight[i].seatsFree);
			printw("Enter number of seats to be booked:");
			scanw("%d",&numTicket);
			if(numTicket >0 && numTicket <= totalflight[i].seatsFree){
				BOOKER bookers[numTicket];
				//totalflight[i].seatsFree=totalflight[i].seatsFree-numTicket;
				fileReadWrite("AirList.txt", totalflight[i].flightnum, numTicket);
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







	






