#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "booking.c"
#include "cancel_flight.c"
#include "admin.c"
#include "Bandhu_chatbot.c"

int admin_login()
{
    ADMIN admin;
    FILE *fptr;

    int row, col, choice;
    getmaxyx(stdscr,row,col);

    move((row/2)-5,(col/2)-3);
    printw("Enter your name: ");
    getstr(admin.name);
    move((row/2)-4,(col/2)-3);
    printw("Enter Ronway ID: ");
    getstr(admin.id);
    move((row/2)-3,(col/2)-3);
    printw("Enter your password: ");
    noecho();
    getstr(admin.pwd);
    echo();

    fptr = fopen("Admins.txt", "r");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }

    while(fread(&admin, sizeof(ADMIN), 1, fptr))
    {
        if(strcmp(admin.name, admin.name) == 0 && strcmp(admin.id, admin.id) == 0 && strcmp(admin.pwd, admin.pwd) == 0)
        {
            move((row/2)-1,(col/2)-3);
            printw("Login successful\n");
            clear();
            printw("1. Add Flight\n");
            printw("2. Cancel Flight\n");
            printw("3. Change Flight Data\n");
            printw("4. View Flights\n");
            scanw("%d", &choice);

            if(choice == 1)
            {
                addFlight();
            }
            else if(choice == 2)
            {
                deleteFlight();
            }
            else if(choice == 3)
            {
                updateFlight();
            }
            else if(choice == 4){
                //loadFlight();
                displayAllFlights();
            }
            break;
        }
        else
        {   
            move((row/2)-1,(col/2)-3);
            printw("Login failed. Try Again\n");
            break;
        }
    }
    fclose(fptr);
    return 0;

}
int user_login()
{
    USER user;
    FILE *fptr;

    int row, col, choice;
    getmaxyx(stdscr,row,col);
    char name[50], pswd[50];
    move((row/2)-5,(col/2)-3);

    printw("Enter your name: ");
    getstr(name);
    move((row/2)-4,(col/2)-3);
    printw("Enter your password: ");
    noecho();
    getstr(pswd);
    echo();

    fptr = fopen("Users.txt", "r");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    int flag=0;
    while(fread(&user, sizeof(USER), 1, fptr))
    {
        // printw("%s %s", user.name, user.pwd);
        // getch();
        if(strcmp(user.name, name) == 0 && strcmp(user.pwd, pswd) == 0)
        {
            flag=1;
            move((row/2)-1,(col/2)-3);
            printw("Login successful\n");
            clear();
            printw("1. Search Flights\n");
            printw("2. Book Tickets\n");
            printw("3. Cancel Tickets\n");
            printw("4. Bandhu -- the chat assistant\n");
            scanw("%d", &choice);

            //loadFlight();

            if(choice == 1)
            {
                char source[100], dest[100], date[100], time[50];
                printw("Enter source: ");
                getstr(source);
                printw("Enter destination: ");
                getstr(dest);
                printw("Enter date: ");
                getstr(date);
                printw("Enter time:");
                getstr(time);
                searchFlight(source, dest, date, time);
            }
            else if(choice == 2)
            {
                char flightnum[50];
                printw("Enter flight number: ");
                getstr(flightnum);
                bookFlight(flightnum);
            }
            else if(choice == 3)
            {
                char pnr[50];
                printw("Enter Ticket Number: ");
                getstr(pnr);
                cancelBooking(pnr);
            }
            else if(choice == 4)
            {
                clear();
                int counter=1;
                printw("Hello %s! I am Bandhu, your flight assistant. How can I help you today?\n", name);
                chatting:
                    if(counter>1)
                    printw("Is there anything else that I can help you with?\n");
                    int f = chat(name);
                    counter+=1;
                switch(f)
                {
                    case 1: 
                    char pnr[50];
                    printw("Please enter the ticket number that you want to cancel: ");
                    getstr(pnr);
                    cancelBooking(pnr);
                    goto chatting;
                    break;

                    case 2: 
                    char flightnum[50];
                    printw("Please enter the flight number which you want to book: ");
                    getstr(flightnum);
                    bookFlight(flightnum);
                    printw("Your ticket has been booked!\n"); 
                    goto chatting;
                    break;

                    default: printw("Thanks!");
                }
            }
            break;
        }
    }
    if(flag==0)
    {
    move((row/2)-1,(col/2)-3);
    printw("Incorrect Username/Password....." );
    move((row/2),(col/2)-3);
    printw("Login failed, try again.");
    move((row/2)+3,(col/2)-3);
    printw("Press any key to go to main!!");
    fclose(fptr);
     return 0;
    }
}
