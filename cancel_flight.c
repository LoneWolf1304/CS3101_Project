#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>






//function to cancel booking
int cancelBooking(char* tick){

    int row,col;
    getmaxyx(stdscr,row,col);
    FILE *fptr;
    BOOKER booking, *bookings;
    int no_of_rec = 0, i;

    fptr = fopen("Booking_List.txt", "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&booking, sizeof(BOOKER), 1, fptr)) 
    {
        no_of_rec++;//count the number of records (each record is a air type variable)
    }
    bookings = (BOOKER*)malloc(no_of_rec*sizeof(BOOKER));
    rewind(fptr);

    i=0;
    while(fread(&booking, sizeof(BOOKER), 1, fptr))
    {
        
        strcpy(bookings[i].name, booking.name);
        strcpy(bookings[i].gender, booking.gender);
        strcpy(bookings[i].type, booking.type);
        strcpy(bookings[i].meal, booking.meal);
        strcpy(bookings[i].seat, booking.seat);
        strcpy(bookings[i].pnr, booking.pnr);
        strcpy(bookings[i].flightnum, booking.flightnum);
        bookings[i].age = booking.age;
        i++;
    }
    fclose(fptr);

    char seats[no_of_rec][10];
    int index=-1;
    move(row/2-1, col/2-20);
    printw("The following booking record is found:");
    move(row/2, col/2-20);
    printw("Name\tGender\tAge\tType\tMeal\tSeat No.");
    int cancelled=0;
    for(int i=0; i<no_of_rec; i++)
    {   
        if(strcmp(bookings[i].pnr, tick)==0)
        {
            move(row/2+1+i, col/2-20);
            printw("%s\t%s\t%d\t%s\t%s\t%s",bookings[i].name,bookings[i].gender,bookings[i].age,bookings[i].type, bookings[i].meal, bookings[i].seat);
            strcpy(seats[i], bookings[i].seat);
            index=i;
            cancelled+=1;
        }
    }
    move(row/2+2+no_of_rec, col/2-20);
    if(index!=-1)
    {
    printw("Do you want to cancel this booking? (y/n): ");
    char ch;
    scanw("%c", &ch);
    switch(ch)
    {

    case 'y':
            char filename[100];
            snprintf(filename, sizeof(filename), "./Seat Matrix/%s.txt", bookings[index].flightnum);
            update_seat_matrix(filename, bookings[index].flightnum, seats, sizeof(seats)/sizeof(seats[0]), "remove");
            fptr = fopen("Booking_List.txt", "w");
            for(int i=0; i<no_of_rec; i++)
            {
                if(strcmp(bookings[i].pnr, tick)!=0)
                {   
                    fwrite(&bookings[i], sizeof(BOOKER), 1, fptr);
                }
            }
            fclose(fptr);
            move(row/2+4+no_of_rec, col/2-20);
            printw("Booking Cancelled Successfully!!\n");
            fileReadWrite("./Seat Matrix/AirList.txt", bookings[index].flightnum, cancelled, "remove");
            break;

    case 'n': 
            move(row/2+4+no_of_rec, col/2-20);
            printw("Booking not cancelled\n");
            break;
    }
    }
    else
    {
        printw("Booking record not found\n");
    }
}

            
