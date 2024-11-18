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
            strcpy(airs[i].source, air.source);
            strcpy(airs[i].destination, air.destination);
            strcpy(airs[i].date, air.date);
            strcpy(airs[i].time, air.time);
            strcpy(airs[i].flightnum, air.flightnum);
            airs[i].adult_price = air.adult_price;
            airs[i].child_price = air.child_price;
            airs[i].infant_price = air.infant_price;
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
    fclose(fptr);
    

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



void print_matrix(char *mon[], char *dat[], int month, int start_row, int start_column)
{
    FILE *fptr;
    int matrixflight[5][7], num; 
    char filename[100];
    snprintf(filename, sizeof(filename), "./Calendar/%d.txt", month);

    fptr = fopen(filename, "r");
    move(start_row, start_column);
    printw("Month %d:", (month+1));
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<7; j++)
        {
            fscanf(fptr, "%d", &num);
            matrixflight[i][j] = num;
        }
    }
    move(start_row+1, start_column);
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(matrixflight[i][j]!=0 && matrixflight[i][j]>=10)
            printw("%d  ", matrixflight[i][j]);
            else if(matrixflight[i][j]!=0 && matrixflight[i][j]<10)
            printw("0%d  ", matrixflight[i][j]);
        }
        move(start_row+1+i, start_column);
        printw("\n");
    }
    fclose(fptr);
}









void searchFlight()
{
    FILE *fptr;
    clear();





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
        
        strcpy(totalflight[i].source, air.source);
		strcpy(totalflight[i].destination, air.destination);
		strcpy(totalflight[i].date, air.date);
		strcpy(totalflight[i].time, air.time);
		strcpy(totalflight[i].flightnum, air.flightnum);
    	totalflight[i].seatsFree = air.seatsFree;
        totalflight[i].adult_price = air.adult_price;
        totalflight[i].child_price = air.child_price;
        totalflight[i].infant_price = air.infant_price;
    	i++;
    }  
    fclose(fptr);





    char month_arr[50][50];
    char date_arr[50][50];
    for(int i=0; i< no_of_rec;i++)
    {
        char date1[50];
        strcpy(date1, totalflight[i].date);
        // month_arr[i] = (char *)malloc(10 * sizeof(char)); // Adjust size as needed
        // date_arr[i] = (char *)malloc(10 * sizeof(char));
        char* token = strtok(date1, "-");
        int a=0;
        //printw("%s dates \n", token);
        while (token != NULL) 
        {
        //printf(" % s\n", token);
        if(a==1) 
        {
        strcpy(month_arr[i], token);
        }
        else if(a==0)
        {
        strcpy(date_arr[i], token);
        }
        token = strtok(NULL, "-");
        a++;
        }
        // printw("%d %s ", i, month_arr[i]);
        // printw("%d %s\n", i, date_arr[i]);
    }





int matrixflight[5][7], num;
    char filename[100];
    int start_row = 2, start_column = 5; // Starting position for the first month
    int months_per_row = 4;             // Number of months per row
    int row_spacing = 8;                // Spacing between calendar rows
    int column_spacing = 32;            // Spacing between calendar columns

    // Initialize ncurses
    initscr();
    clear();
    
    cbreak();

    // Loop through all months (0 = January, 11 = December)
    char *Month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    for (int month = 0; month < 12; month++) 
    {
        // Calculate the row and column for this month's position
        int row = month / months_per_row;                // Row index (0 to 2)
        int col = month % months_per_row;                // Column index (0 to 3)
        int current_row = start_row + row * row_spacing; // Adjust row spacing
        int current_column = start_column + col * column_spacing; // Adjust column spacing


        // int index=0;
        // for(int j2=0; j2<sizeof(date_arr)/sizeof(date_arr[0]);j2++)
        // {
        //     int dat = (atoi(date_arr[j2])==(month+1)); 
        //     if(atoi(month_arr[j2])==(month+1))
        //     {
        //         index=j2;
        //     }
        // }



        // Open the corresponding file
        snprintf(filename, sizeof(filename), "./Calendar/%d.txt", month);
        fptr = fopen(filename, "r");
        if (fptr == NULL) {
            mvprintw(current_row, current_column, "File Error!");
            continue;
        }

        // Read the matrix for the current month
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                fscanf(fptr, "%d", &num);
                matrixflight[i][j] = num;
            }
        }
        fclose(fptr);
        start_color();
        // Print the month header
        mvprintw(current_row, current_column, "    %s", Month[month]);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        // Print the calendar matrix
        for (int i = 0; i < 5; i++) {
            move(current_row + 1 + i, current_column);
            for (int j = 0; j < 7; j++) {
                if (matrixflight[i][j] != 0 && matrixflight[i][j] >= 10)
                {
                    int index=-1;
                    for(int j2=0; j2<sizeof(date_arr)/sizeof(date_arr[0]);j2++)
                    {
                        int dat = (atoi(date_arr[j2])); 
                        //printw(" DATES %s DATES \n", date_arr[j2]);
                        if(matrixflight[i][j] == dat)
                         index=j2;
                        
                    }
                    if(index!= -1 && atoi(month_arr[index])==(month+1))
                    {
                        attron(COLOR_PAIR(2));
                        printw("%d  ", matrixflight[i][j]);
                        attroff(COLOR_PAIR(2));
                    }
                    else
                    {
                        printw("%d  ", matrixflight[i][j]);
                    }
                    

                }
                else if (matrixflight[i][j] != 0 && matrixflight[i][j] < 10)
                {
                    //printw("0%d  ", matrixflight[i][j]);
                    int index=-1;
                    for(int j2=0; j2<sizeof(date_arr)/sizeof(date_arr[0]);j2++)
                    {
                        int dat = (atoi(date_arr[j2])); 
                        //printw(" DATES %s DATES \n", date_arr[j2]);
                        if(matrixflight[i][j] == dat)
                         index=j2;
                        
                    }
                    if(index!= -1 && atoi(month_arr[index])==(month+1))
                    {
                        attron(COLOR_PAIR(2));
                        printw("%d  ", matrixflight[i][j]);
                        attroff(COLOR_PAIR(2));
                    }
                    else
                    {
                        printw("0%d  ", matrixflight[i][j]);
                    }
                }
                else
                    printw("    "); // Empty days
            }
        }
    }




	char src[100], dest[100], dat[100], time[50];
    int row,col;
    getmaxyx(stdscr,row,col);
                move(row-8, col/2-1);
                printw("Flight Search");
                move((row)-6,(col/2)-3);
                printw("Enter source: ");
                getstr(src);
                if(empty_input(src))
                {   
                    move((row)-3,(col/2)-3);
                    printw("Source cannot be empty\n");

                    move((row)-2,(col/2)-3);
                    printw("Press any key to go to main interface");
                    //return 0;
                }

                move((row)-5,(col/2)-3);
                printw("Enter destination: ");
                getstr(dest);
                printw("%s", dest);
                if(empty_input(dest))
                {   
                    move((row)-3,(col/2)-3);
                    printw("Destination cannot be empty\n");

                    move((row)-2,(col/2)-3);
                    printw("Press any key to go to main interface");
                    //return 0;
                }

                move((row)-4,(col/2)-3);
                printw("Enter date: ");
                getstr(dat);
                printw("%s", dat);
                getch();
                if(empty_input(dat))
                {   
                    move((row)-3,(col/2)-3);
                    printw("Date cannot be empty\n");

                    move((row)-2,(col/2)-3);
                    printw("Press any key to go to main interface");
                    //return 0;
                }

char destination[50];
strcpy(destination, dest);
char source[50];
strcpy(source, src);
char date[50];
strcpy(date, dat);
getch();	
    
clear();



	int size = no_of_rec;
	  //function to search flights
	int flag=0;
    int x,y;
    getmaxyx(stdscr, y, x);
    move(y/2-1, x/2-25);
	printw("Available flight from %s to %s on %s:\n",source, destination,date);
	for (int i =0; i < size; i++)
    {
        if(strcmp(totalflight[i].source,source) == 0 &&
		   strcmp(totalflight[i].destination,destination) == 0 &&
		   strcmp(totalflight[i].date,date) == 0)
        {
        char flight_details[300];
        move(y/2+1+flag, x/2-25);
        
        printw("Flight Number: %s\t Seats Available: %d \t Time of Departure: %s", totalflight[i].flightnum, totalflight[i].seatsFree, totalflight[i].time);
		printw(flight_details);
		flag++;
		}
	}
	if(flag==0)
    {
		int rowc, colc;
    	getmaxyx(stdscr,rowc,colc);
		int numRows=0;
	move((rowc/2)-8+numRows, (colc/2));
	printw("Sorry ! No flights found\n");
	move((rowc/2)-10+numRows+4, (colc/2));
	printw("Press any key to continue!");
	}


}









typedef struct {
    char username[50];
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





int bookFlight(char* flightnum, char* usr)
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
        strcpy(totalflight[i].source, air.source);
		strcpy(totalflight[i].destination, air.destination);
		strcpy(totalflight[i].date, air.date);
		strcpy(totalflight[i].time, air.time);
		strcpy(totalflight[i].flightnum, air.flightnum);
        totalflight[i].adult_price = air.adult_price;
        totalflight[i].child_price = air.child_price;
        totalflight[i].infant_price = air.infant_price;
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
            snprintf(filename, sizeof(filename), "./Seat Matrix/%s.txt", flightnum);

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
                    strcpy(bookers[j].username, usr);
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
                        bookers[j].price = totalflight[i].infant_price; ;
            
                    }
                    else if (bookers[j].age < 12){
                        strcpy(bookers[j].type, "Child");
                        bookers[j].price =  totalflight[i].child_price;
                    }
                    else{
                        strcpy(bookers[j].type, "Adult");
                        bookers[j].price =  totalflight[i].adult_price;
                    }
                }
                

            move(y/2-8+4*numTicket, x/2-5);
            printw("Enter seat numbers:");
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
                printw("Name\tGender\tAge\tType\tMeal\tSeat No.\t Price:\n\n");
                double s=0.0;
                for(int j=0; j<numTicket; j++)
                {
                    move((row/2)+4+j,(col/2)-27);
                    printw("%s\t%s\t%d\t%s\t%s\t%s\t%f\n",bookers[j].name,bookers[j].gender,bookers[j].age,bookers[j].type, bookers[j].meal, bookers[j].seat,bookers[j].price);
                    s+=bookers[j].price;
			    }
                move((row/2)+numTicket+6,(col/2)-27);
                printw("Total Price: %0.2f\n",s);
                move((row/2)+numTicket+10,(col/2)-27);
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

    for (i =0 ; i < numRows; i++) {
		move((rowc/2)-10+i, colc/2);
        printw("%s", art[i]);
    }
	move((rowc/2)-8+numRows, (colc/2));
	printw("Flight not found");
	return 0;
}



















