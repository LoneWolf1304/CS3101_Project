#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>



//add additional flight as an admin
flight *totalflight=NULL;
int no_of_records = 0;

void fileAdminWrite(){

    FILE *fptr;
    int i;

    fptr = fopen("/mnt/d/ronit/IISER-K/5 SEM/CS3101/CS3101 project/CS3101_project_own/Seat Matrix/AirList.txt", "a");

    if(fptr == NULL)
    {
        printw("Error opening file!\n");
        exit(1);
    }
    fwrite(&totalflight[no_of_records-1], sizeof(flight), 1, fptr);

    fclose(fptr);
}


void loadFlight(){
    FILE *fptr =fopen("/mnt/d/ronit/IISER-K/5 SEM/CS3101/CS3101 project/CS3101_project_own/Seat Matrix/AirList.txt", "r");
    if(fptr == NULL)
    {
        printw("Error opening file!\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    rewind(fptr);

    no_of_records = fileSize/sizeof(flight);
    
    totalflight = (flight*)malloc(no_of_records*sizeof(flight));

    if (totalflight == NULL){
        printw("Memory allocation failed.\n");
        return;
    }

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

    flight* temp=(flight*)realloc(totalflight,(no_of_records+1)*sizeof(flight));

    if (temp == NULL){
        printw("Memory allocation failed.\n");
        return;
    }

    totalflight = temp;


    flight newFlight;


    printw("Enter Flight Number:");
    scanw("%s", newFlight.flightnum);
    printw("Enter number of seats:");
    scanw("%d", &newFlight.seatsFree);
    printw("Enter Source:");
    scanw("%s", newFlight.source);
    printw("Enter Destination:");
    scanw("%s", newFlight.destination);
    printw("Enter Date (DD-MM-YYYY):");
    scanw("%s", newFlight.date);
    printw("Enter Departure Time:");
    scanw("%s", newFlight.time);

    

    
    totalflight[no_of_records] = newFlight;
    no_of_records++;

    printw("Flight added successfully.\n");
    loadFlight();
}


//Function to modify flight details

void updateFlight(){
    
    char flightnum[50];
    int i ,flag=0;
    printw("Enter the flight number of the flight you want to modify:");
    scanw("%s", flightnum);

    
    for(i = 0; i < no_of_records; i++){
        if(strcmp(totalflight[i].flightnum, flightnum) == 0){

            flag = 1;
            printw("Flight found.\n");

            //current flight details
            printw("Current Flight Number: %s\n", totalflight[i].flightnum);
            printw("Current number of seats: %d\n", totalflight[i].seatsFree);
            printw("Current Source: %s\n", totalflight[i].source);
            printw("Current Destination: %s\n", totalflight[i].destination);
            printw("Current Date: %s\n", totalflight[i].date);
            printw("Current Departure Time: %s\n", totalflight[i].time);

            //update details

            printw("Enter new Flight Number:");
            scanw("%s", totalflight[i].flightnum);
            printw("Enter new number of seats:");
            scanw("%d", &totalflight[i].seatsFree);
            printw("Enter new Source:");
            scanw("%s", totalflight[i].source);
            printw("Enter new Destination:");
            scanw("%s", totalflight[i].destination);
            printw("Enter new Date (DD-MM-YYYY):");
            scanw("%s", totalflight[i].date);
            printw("Enter new Departure Time:");
            scanw("%s", totalflight[i].time);

            fileAdminWrite();
            printw("Flight details modified successfully.\n");
            return;
        }
    }

    if(flag == 0){
        printw("Flight not found.\n");
    }
}


//Function to delete a flight

void deleteFlight(){

    char flightnum[50];
    int i, j, flag=0;
    printw("Enter the flight number of the flight you want to delete:");
    scanw("%s", flightnum);

    for(i = 0; i < sizeof(totalflight)/sizeof(flight); i++){
        if(strcmp(totalflight[i].flightnum, flightnum) == 0){

            flag = 1;
            printw("Flight found.\n");

            for(j = i; j < sizeof(totalflight)/sizeof(flight) - 1; j++){
                totalflight[j] = totalflight[j+1];
            }

            
            flight *temp = (flight *) realloc(totalflight,sizeof(flight)*(no_of_records-1));
            if(temp == NULL){
                printw("Memory allocation failed.\n");
                return;
            }
            totalflight = temp;
            no_of_records--;

            fileAdminWrite();
            printw("Flight deleted successfully.\n");
            return;
        }
    }

    if(flag == 0){
        printw("Flight not found.\n");
    }


}


//function to display all flights in the database

void displayAllFlights(){
    printw("Total number of flights: %d\n", no_of_records);
    if (no_of_records == 0) {
        printw("No flights available.\n");
        return;
    }

    int i;
    for(i = 0; i < no_of_records; i++){
        printw("Flight Number: %s\n", totalflight[i].flightnum);
        printw("Number of seats: %d\n", totalflight[i].seatsFree);
        printw("Source: %s\n", totalflight[i].source);
        printw("Destination: %s\n", totalflight[i].destination);
        printw("Date: %s\n", totalflight[i].date);
        printw("Departure Time: %s\n", totalflight[i].time);
        printw("\n");
    }


}

