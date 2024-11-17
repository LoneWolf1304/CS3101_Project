#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include "./Seat Matrix/seat_matrix.c"


//add additional flight as an admin
flight *totalflight=NULL;
int no_of_records = 0;

void fileAdminWrite(){

    FILE *fptr;
    int i;

    fptr = fopen("./Seat Matrix/AirList.txt", "a");

    if(fptr == NULL)
    {
        printw("Error opening file!\n");
        exit(1);
    }
    fwrite(&totalflight[no_of_records-1], sizeof(flight), 1, fptr);

    fclose(fptr);
}


void loadFlight(){
    FILE *fptr =fopen("./Seat Matrix/AirList.txt", "r");
    if(fptr == NULL)
    {
        printw("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);

    no_of_records = fileSize/sizeof(flight);
    
    //totalflight = (flight*)malloc(no_of_records*sizeof(flight));

    // if (totalflight == NULL){
    //     printw("Memory allocation failed.\n");
    //     return;
    // }

    for(int i = 0; i < no_of_records; i++){
        fread(&totalflight[i], sizeof(flight), 1, fptr);
    }

    fclose(fptr);


}


void addFlight(){ 

    if(no_of_records == 250){
        printf("No more flights can be added.\n");
        return;
    }

    // flight* temp=(flight*)realloc(totalflight,(no_of_records+1)*sizeof(flight));

    // if (temp == NULL){
    //     printw("Memory allocation failed.\n");
    //     return;
    // }

    // totalflight = temp;


    flight newFlight;

    int row, col;
    getmaxyx(stdscr, row, col);

    move(row/2-8, col/2-10);
    printw("Enter the following details:\n");
    //printw("----------------------------\n");
    
    move(row/2-7, col/2-10);
    printw("Enter Flight Number:");
    scanw("%s", newFlight.flightnum);

    move(row/2-6, col/2-10);
    printw("Enter number of seats:");
    scanw("%d", &newFlight.seatsFree);

    move(row/2-5, col/2-10);
    printw("Enter Source:");
    scanw("%s", newFlight.source);

    move(row/2-4, col/2-10);
    printw("Enter Destination:");
    scanw("%s", newFlight.destination);

    move(row/2-3, col/2-10);
    printw("Enter Date (DD-MM-YYYY):");
    scanw("%s", newFlight.date);

    move(row/2-2, col/2-10);
    printw("Enter Departure Time:");
    
    scanw("%s", newFlight.time);

    

    
    //totalflight[no_of_records] = newFlight;
    FILE *fptr;
    fptr = fopen("./Seat Matrix/AirList.txt", "a");

    move(row/2-1, col/2-10);
    printw("Flight added successfully.\n");
    fwrite(&newFlight, sizeof(flight), 1, fptr);
    fclose(fptr);
    seat(newFlight.flightnum, 60);
    no_of_records++;
        //loadFlight();
}


//Function to modify flight details

void updateFlight(){
    

    char flightnum[50];
    int flag=0;
    
    int row, col;
    getmaxyx(stdscr, row, col);

    move(row/2-8, col/2-10);
    printw("Enter the flight number of the flight you want to modify:");
    scanw("%s", flightnum);



    FILE *fptr =fopen("./Seat Matrix/AirList.txt", "r+");
    if(fptr == NULL)
    {
        printw("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);


    int i=0, cnt=0;
    flight air, *airs;
    no_of_records = fileSize/sizeof(flight);
    airs = (flight*)malloc(no_of_records*sizeof(flight));

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
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
    

    
    for(i = 0; i < no_of_records; i++){
        if(strcmp(airs[i].flightnum, flightnum) == 0)
        {
            int x, y;
            getmaxyx(stdscr, y, x);
            move(y/2-2, x/2-10);

            flag = 1;
            printw("Flight found.\n");

            //current flight details
            printw("Current Flight Number: %s\n", airs[i].flightnum);
            printw("Current number of seats: %d\n", airs[i].seatsFree);
            printw("Current Source: %s\n", airs[i].source);
            printw("Current Destination: %s\n", airs[i].destination);
            printw("Current Date: %s\n", airs[i].date);
            printw("Current Departure Time: %s\n", airs[i].time);

            //update details

            printw("Enter new Flight Number:");
            scanw("%s", airs[i].flightnum);
            printw("Enter new number of seats:");
            scanw("%d", &airs[i].seatsFree);
            printw("Enter new Source:");
            scanw("%s", airs[i].source);
            printw("Enter new Destination:");
            scanw("%s", airs[i].destination);
            printw("Enter new Date (DD-MM-YYYY):");
            scanw("%s", airs[i].date);
            printw("Enter new Departure Time:");
            scanw("%s", airs[i].time);

            //fileAdminWrite();
            print_centre("Flight details modified successfully.\n");
            return;
        }
    }

    if(flag == 0){
        print_centre("Flight not found.\n");
    }
}


//Function to delete a flight

void deleteFlight(){

    char flightnum[50];
    int flag=0;
    printw("Enter the number of the flight you want to delete:");
    scanw("%s", flightnum);

    // for(i = 0; i < sizeof(totalflight)/sizeof(flight); i++)
    // {
    //     if(strcmp(totalflight[i].flightnum, flightnum) == 0){

    //         flag = 1;
    //         printw("Flight found.\n");

    //         for(j = i; j < sizeof(totalflight)/sizeof(flight) - 1; j++){
    //             totalflight[j] = totalflight[j+1];
    //         }

            
    //         flight *temp = (flight *) realloc(totalflight,sizeof(flight)*(no_of_records-1));
    //         if(temp == NULL){
    //             printw("Memory allocation failed.\n");
    //             return;
    //         }
    //         totalflight = temp;
    //         no_of_records--;

    //         fileAdminWrite();
    //         printw("Flight deleted successfully.\n");
    //         return;
    //     }
    // }

    FILE *fptr =fopen("./Seat Matrix/AirList.txt", "r+");
    if(fptr == NULL)
    {
        print_centre("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);


    int i=0, cnt=0;
    flight air, *airs;
    no_of_records = fileSize/sizeof(flight);
    airs = (flight*)malloc(no_of_records*sizeof(flight));

    while(fread(&air, sizeof(flight), 1, fptr)) //reading each record
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

    fptr = fopen("./Seat Matrix/AirList.txt", "w");
    if(fptr == NULL)
    {
        print_centre("Error opening file!\n");
        free(airs);
        exit(1);
    }
    for(i = 0 ; i < no_of_records; i++)
    {
        if(strcmp(airs[i].flightnum, flightnum) == 0)//check if this is the record to be updated
        {
            flag = 1;
            continue;
        }
        else
        fwrite(&airs[i], sizeof(flight), 1, fptr); //overwriting the file with the updated record (even the unchanged records are overwritten)       
    }
    
    fclose(fptr);
    print_centre("Flight successfully deleted!\n");
    if(flag == 0){
        print_centre("Flight not found.\n");
    }
}


//function to display all flights in the database

void displayAllFlights()
{

    flight details;
    FILE *fptr =fopen("./Seat Matrix/AirList.txt", "r");
    if(fptr == NULL)
    {
        print_centre("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);

    // no_of_records = fileSize/sizeof(flight);


    // printw("Total number of flights: %d\n", no_of_records);
    // if (no_of_records == 0) {
    //     printw("No flights available.\n");
    //     return;
    // }
int x,y;
getmaxyx(stdscr, y, x);
    int i=0;
    move(y/2-12, x/2-6);
    printw("All the available flights are: ");
    while(fread(&details, sizeof(flight), 1, fptr))
    {
        move(y/2-13+7*i, x/2-6);
        printw("Flight Number: %s\n", details.flightnum);
        move(y/2-12+7*i, x/2-6);
        printw("Number of seats: %d\n", details.seatsFree);
        move(y/2-11+7*i, x/2-6);
        printw("Source: %s\n", details.source);
        move(y/2-10+7*i, x/2-6);
        printw("Destination: %s\n", details.destination);
        move(y/2-9+7*i, x/2-6);
        printw("Date: %s\n", details.date);
        move(y/2-8+7*i, x/2-6);
        printw("Departure Time: %s\n", details.time);
        move(y/2-7+7*i, x/2-6);
        printw("\n");
        i++;
    }

    // int i;
    // for(i = 0; i < no_of_records; i++){
    //     printw("Flight Number: %s\n", totalflight[i].flightnum);
    //     printw("Number of seats: %d\n", totalflight[i].seatsFree);
    //     printw("Source: %s\n", totalflight[i].source);
    //     printw("Destination: %s\n", totalflight[i].destination);
    //     printw("Date: %s\n", totalflight[i].date);
    //     printw("Departure Time: %s\n", totalflight[i].time);
    //     printw("\n");
    // }


}

