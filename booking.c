#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<time.h>
#include "airplane_list.h"

#define ADULT_PRICE 5000
#define CHILD_PRICE 3000
#define INFANT_PRICE 0

int empty_input(const char *str) {
    return str == NULL || str[0] == '\0';
}

#define MAX_FLIGHTS 50
#define MAX_SEATS 60
#define MAX_BOOKINGS 50

void print_centre(const char *str){
    int row, col;
    getmaxyx(stdscr, row, col);
    int x=(col-strlen(str))/2;
    int y=row/2-2;
    move(y,x);
    printw("%s", str);


}



typedef struct {

	char name[100];
	char flightnum[50];

} booking;
   // array of structures
//int size = sizeof(totalflight)/sizeof(flight);
void update_seat_matrix(char* filename, char* airnum, char seats[][10], int size, char* mode)
{
    FILE *fptr;
    int matrixA[10][6], num;
	//Accessing file a.txt and storing value in matrixA
	fptr = fopen(filename, "r");
	for(int i=0; i<10; i++){
		for(int j=0; j<6; j++){
			fscanf(fptr, "%d", &num);
			matrixA[i][j] = num;
		}
	}
	fclose(fptr);

    if(strcmp(mode, "add")==0)
    {
        for(int j=0; j<size; j++)
        {
            int row = seats[j][0]-49;
            int col = seats[j][1] - 'A';
            matrixA[row][col] = 1;
        }
    }
    else if(strcmp(mode, "remove")==0)
    {
        for(int j=0; j<size; j++)
        {
            int row = seats[j][0]-49;
            int col = seats[j][1] - 'A';
            matrixA[row][col] = 0;
        }

    }
    
    

    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printw("Error opening file %s\n", filename);
        getch();
        return;
    }

    // Write a 10x6 matrix of random numbers to the file
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            {
                // fprintf(fptr, " %d ", rand() % 2);
                fprintf(fptr, " %d ", matrixA[i][j]);
            } // Add a space between numbers
        }
        fprintf(fptr, "\n");
    }

    // Close the file
    fclose(fptr);
}




void fileReadWrite(char* filename, char* airnum, int seats, char *mode)

{
    FILE *fptr;
    flight air, *airs;
    int no_of_rec = 0, i;


    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printw("Error opening file!\n");
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
                if(strcmp(mode, "add")==0)
                    airs[i].seatsFree -=seats;//updating
                    else if(strcmp(mode, "remove")==0)
                    airs[i].seatsFree +=seats;//updating
            }
            i++;
        }
    // else if(strcpy(mode, "remove")==0)
    // {
    //     while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
    //     {
    //         //printf("Current position: %ld  ", ftell(fptr));
    //         //printf ("Title = %s id = %s stock = %d\n", air.title, 
    //         //air.id, air.no); 
            
    //         strcpy(airs[i].source, air.source);
    //         strcpy(airs[i].destination, air.destination);
    //         strcpy(airs[i].date, air.date);
    //         strcpy(airs[i].time, air.time);
    //         strcpy(airs[i].flightnum, air.flightnum);
    //         airs[i].seatsFree = air.seatsFree;
    //         if(strcmp(air.flightnum, airnum) == 0)//check if this is the record to be updated
    //         {
    //             airs[i].seatsFree +=seats;//updating
    //         }
            
    //         i++;
    //     }  
    //}

    fclose(fptr);
    
    //printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        free(airs);
        exit(1);
    }

    for(i = 0 ; i < no_of_rec ; i++)
    {
        fwrite(&airs[i], sizeof(flight), 1, fptr); //overwriting the file with the updated record (even the unchanged records are overwritten)       
    }
    
    fclose(fptr);
    free(airs);
}





void searchFlight(char* source,  char* destination,  char* date){
	
	FILE *fptr;
    flight air;
	flight *totalflight;
    int no_of_rec = 0, i;
    fptr = fopen("./Seat Matrix/AirList.txt", "r");

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

    char header[300];
    printw(header, sizeof(header), "Available flight from %s to %s on %s:", source, destination, date);
    printw(header);


	int size = no_of_rec;
	  //function to search flights
	int flag=0;
    int x,y;
    getmaxyx(stdscr, y, x);
    move(y/2-1, x/2-25);
	printw("Available flight from %s to %s on %s:\n",source,destination,date);
	for (int i =0; i < size; i++)
    {
		// if(strcmp(totalflight[i].source,source) == 0 &&
		//    strcmp(totalflight[i].destination,destination) == 0 &&
		//    strcmp(totalflight[i].date,date) == 0 && strcmp(totalflight[i].time,tim) == 0)
        if(strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0)
        {
        char flight_details[300];
        move(y/2+1+flag, x/2-25);
        // snprintf(flight_details, sizeof(flight_details), "Flight Number: %s\t Seats Available: %d \t Time of Departure: %s", totalflight[i].flightnum, totalflight[i].seatsFree, totalflight[i].time);
        printw("Flight Number: %s\t Seats Available: %d \t Time of Departure: %s", totalflight[i].flightnum, totalflight[i].seatsFree, totalflight[i].time);

		//printw("Flight Available !\n");
		printw(flight_details);
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


/*

price: 


*/
typedef struct {
	char name[50];
	int age;
	char gender[10];
    char type[10];//passenger type(adult, child, infant)
    char meal[20];
    char pnr[20];
    char seat[20];
    char flightnum[20];
    double price; 
} BOOKER;

BOOKER bookers[MAX_BOOKINGS];


void addBooker(char *filename, BOOKER booker[], int numTicket, char *flightnum)
{
    FILE *fptr;
    fptr = fopen(filename, "a");
    if(fptr == NULL)
    {
        printf("Error opening file!\n");
    }
    for(int i=0; i<numTicket; i++)
    {
        fwrite(&booker[i], sizeof(BOOKER), 1, fptr);     
    }
    fclose(fptr);
}





int bookFlight(char* flightnum)
{

    srand(time(0));
    FILE *fptr;
    flight air, *airs;
    int no_of_rec = 0, i;
	flight *totalflight;

    fptr = fopen("./Seat Matrix/AirList.txt", "r+");

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

	for(int i=0; i< size;i++)
    {
		if(strcmp(totalflight[i].flightnum, flightnum)==0)
        {   
            int row,col;
            getmaxyx(stdscr,row,col);
            char header[300];
            snprintf(header, sizeof(header), "Flight %s from %s to %s on %s at %s", totalflight[i].flightnum, totalflight[i].source, totalflight[i].destination, totalflight[i].date, totalflight[i].time); 
            move(row/2-2, col/2-3);
			printw("The number of seats available: %d\n",totalflight[i].seatsFree);
            move(row/2-1, col/2-3);
            printw("Enter number of seats to be booked: ");
			scanw("%d",&numTicket);
            move(row/2, col/2-3);
            printw("Press any key to continue book tickets!");
            getch();
            clear();

			if(numTicket >0 && numTicket <= totalflight[i].seatsFree)
            {
				BOOKER bookers[numTicket];
                FILE *fptr;
            int matrixflight[10][6], num; 
            char filename[100];
            snprintf(filename, sizeof(filename), "/mnt/d/ronit/IISER-K/5 SEM/CS3101/CS3101 project/CS3101_Project/Seat Matrix/%s.txt", flightnum);

            fptr = fopen(filename, "r");
            for(int i=0; i<10; i++)
            {
                for(int j=0; j<6; j++)
                {
                    fscanf(fptr, "%d", &num);
                    matrixflight[i][j] = num;
                }
            }
            fclose(fptr);
            //Printing flight matrix
            printw("Seats available for the flight \n\n\n\t  Front\n\n");
            printw("\tA B C   D E F\n\n\n");
            
            for(int i=0; i<10; i++)
            {
                
                for(int j=0; j<6; j++)
                {
                    if(j==3)
                    {
                        printw("  %d ", matrixflight[i][j]);
                    }
                    else if(j==0)
                    {
                        printw("%d\t%d ", (i+1), matrixflight[i][j]);
                    }
                    else
                    printw("%d ", matrixflight[i][j]);
                }
                printw("\n");
            }
            printw("\n\t Rear\n");


                int x,y;
                getmaxyx(stdscr, y, x);

                for(int j=0; j<numTicket; j++)
                {   
                    move(y/2-12+5*j, x/2-5);
                    printw("Enter name of passenger %d: ",j+1);
                    scanw("%s",bookers[j].name);
                    move(y/2-11+5*j, x/2-5);
                    printw("Enter age of passenger %d: ",j+1);
                    scanw("%d",&bookers[j].age);  
                    move(y/2-10+5*j, x/2-5);
                    printw("Enter gender (M/F): ");
                    scanw("%s",bookers[j].gender);
                    move(y/2-9+5*j, x/2-5);
                    printw("Enter meal option (Veg/Non-Veg/No): ");
                    scanw("%s",bookers[j].meal);
                    move(y/2-8+5*j, x/2-5);

                    if (bookers[j].age < 2){
                        strcpy(bookers[j].type, "Infant");
                        bookers[j].price = INFANT_PRICE;
            
                    }
                    else if (bookers[j].age < 12){
                        strcpy(bookers[j].type, "Child");
                        bookers[j].price = CHILD_PRICE;
                    }
                    else{
                        strcpy(bookers[j].type, "Adult");
                        bookers[j].price = ADULT_PRICE;
                    }
                }
                

            move(y/2-8+4*numTicket, x/2-5);
            printw("Enter seat numbers:\n");
            char seats[numTicket][10];
            double total_price = 0.0;

            for(int i=0; i<numTicket; i++)
            {
                move(y/2-7+4*numTicket+1+i, x/2-5);
                getstr(bookers[i].seat);
                strcpy(seats[i], bookers[i].seat);
                strcpy(bookers[i].flightnum,flightnum);
                total_price += bookers[i].price;
            }
            int pn = (rand() % 900)+100;
            char pnrs[20]; 
            snprintf(pnrs, sizeof(pnrs), "%d", pn);
            strcat(pnrs, flightnum);
            for(int i=0; i<numTicket; i++)
            {
                strcpy(bookers[i].pnr, pnrs);
            }
            update_seat_matrix(filename, flightnum, seats, sizeof(seats)/sizeof(seats[0]), "add");
             clear(); 
                int row, col;
                getmaxyx(stdscr,row,col);
                move((row/2)-5,(col/2)-11);
                printw("Your Booking is Successful !");
                move((row/2)-3,(col/2)-15);
                printw("Ticket Summary Generated\n\n ");

				fileReadWrite("./Seat Matrix/AirList.txt", totalflight[i].flightnum, numTicket, "add");
                move((row/2)-1,(col/2)-27);
                printw("Ticket Number: %s \n\n", pnrs);
                move((row/2),(col/2)-27);
                printw("Flight Number: %s \n\n", flightnum);
                move((row/2)+3,(col/2)-27);
                printw("Name\tGender\tAge\tType\tMeal\tSeat No.\t\t Price:\n\n");
                for(int j=0; j<numTicket; j++)
                {
                    move((row/2)+4+j,(col/2)-27);
                    printw("%s\t%s\t%d\t%s\t%s\t%s\t\t%0.2f\n",bookers[j].name,bookers[j].gender,bookers[j].age,bookers[j].type, bookers[j].meal, bookers[j].seat,bookers[j].price);
			    }
                move((row/2)+numTicket+8,(col/2)-27);
                printw("Thank you for your booking! Bon Voyage!!\n");

                addBooker("Booking_List.txt", bookers, numTicket, flightnum);
                return 1;
            }
            else
            {
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
    //int i=0;
    for (i =0 ; i < numRows; i++) {
		move((rowc/2)-10+i, colc/2);
        printw("%s", art[i]);
    }
	move((rowc/2)-8+numRows, (colc/2));
	printw("Flight not found");
	return 0;
}














