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
    if(empty_input(admin.name))
    {   
        move((row/2)-1,(col/2)-3);
        printw("Name cannot be empty !\n");

        move((row/2),(col/2)-3);
        printw("Press any key to go to main interface");
        //getch();
        return 0;
    }


    move((row/2)-4,(col/2)-3);
    printw("Enter Ronway ID: ");
    getstr(admin.id);
    if(empty_input(admin.id))
    {   
        move((row/2)-1,(col/2)-3);
        printw("ID cannot be empty\n");

        move((row/2),(col/2)-3);
        printw("Press any key to go to main interface");
        return 0;
    }

    move((row/2)-3,(col/2)-3);
    printw("Enter your password: ");
    noecho();
    getstr(admin.pwd);
    echo();
    if(empty_input(admin.pwd))
    {   
        move((row/2)-1,(col/2)-3);
        printw("Password cannot be empty\n");

        move((row/2),(col/2)-3);
        printw("Press any key to go to main interface");
        return 0;
    }

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
            adm_ut:
            move((row/2)-10,(col/2)-6);
            printw("Admin Utilities");

            move((row/2)-8,(col/2)-6);
            printw("1. Add Flight\n");

            move((row/2)-7,(col/2)-6);
            printw("2. Cancel Flight\n");

            move((row/2)-6,(col/2)-6);
            printw("3. Change Flight Data\n");

            move((row/2)-5,(col/2)-6);
            printw("4. View Flights\n");

            move((row/2)-4,(col/2)-6);
            printw("5. Logout\n");

            move((row/2),(col/2)-6);
            printw("Enter your choice: ");
            scanw("%d", &choice);

            clear();

            if(choice == 1)
            {
                addFlight();
                getch();
                clear();
                goto adm_ut;
            }
            else if(choice == 2)
            {
                deleteFlight();
                getch();
                clear();
                goto adm_ut;
            }
            else if(choice == 3)
            {
                updateFlight();
                getch();
                clear();
                goto adm_ut;
            }
            else if(choice == 4){
                //loadFlight();
                displayAllFlights();
                getch();
                clear();
                goto adm_ut;
            }
            else if(choice == 5)
            {
                break;
            }
            else
            {
                move((row/2)-1,(col/2)-3);
                printw("Invalid choice\n");
                getch();
                clear();
                goto adm_ut;
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
    if(empty_input(name))
    {   
        move((row/2)-1,(col/2)-3);
        printw("Name cannot be empty\n");

        move((row/2)+1,(col/2)-3);
        printw("Press any key to go to main interface");
        return 0;
    }


    move((row/2)-4,(col/2)-3);
    printw("Enter your password: ");
    noecho();
    getstr(pswd);
    if(empty_input(name))
    {   
        move((row/2)-1,(col/2)-3);
        printw("Wrong Password\n");

        move((row/2)+1,(col/2)-3);
        printw("Press any key to go to main interface");
        return 0;
    }
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
            move((row/2)-1,(col/2)-10);
            printw("Login successful...Press any key to go to next page!\n");
            getch();
            clear();
            utils:
            move((row/2)-8,(col/2)-4);
            printw("User Utilities");
            move((row/2)-5,(col/2)-7);
            printw("1. Search Flights\n");
            

            move((row/2)-4,(col/2)-7);
            printw("2. Book Tickets\n");
           

            move((row/2)-3,(col/2)-7);
            printw("3. Cancel Tickets\n");
            move((row/2)-2,(col/2)-7);
            printw("4. View Records\n");
            move((row/2)-1,(col/2)-7);
            printw("5. Bandhu -- the chat assistant\n");
            move((row/2),(col/2)-7);
            printw("6. Logout\n");
            move((row/2)+2,(col/2)-7);
            printw("Enter your choice: ");
            scanw("%d", &choice);
            clear();

            //loadFlight();

            if(choice == 1)
            {
                
                int rec = searchFlight();
                if(rec!=0)
                {
                    move(row/2+2+rec, col/2-25);
                    printw("Do you want to book the flight? (y/n): ");
                    char chc = getch();
                    clear();
                    switch (chc)
                    {
                    case 'y': goto booking_page;
                    break;
                    case 'n': break;
                    }
                }
                getch();
                clear();
                goto utils;
            }
            else if(choice == 2)
            {
                booking_page:
                char flightnum[50];
                move((row/2)-5,(col/2)-3);
                printw("Enter flight number: ");
                getstr(flightnum);
                bookFlight(flightnum, name);
                getch();
                clear();
                goto utils;
            }
            else if(choice == 3)
            {
                char pnr[50];
                move((row/2)-5,(col/2)-3);
                printw("Enter Ticket Number: ");
                getstr(pnr);
                cancelBooking(pnr);
                getch();
                clear();
                goto utils;
            }
            else if(choice == 4)
            {

                FILE *fptr;
                    BOOKER booking;
                    fptr = fopen("Booking_List.txt", "r+");
                    if(fptr == NULL)
                    {
                        printw("Error opening file!\n");
                        exit(1);
                    }
                    int i=0;
                    move(row/2-1, col/2-30);
                    printw("The following booking record is found for user:");
                    move(row/2, col/2-30);
                    printw("Name\tGender\tAge\tType\tMeal\tSeat No.\tFlight No.\tTicket No.");
                    while(fread(&booking, sizeof(BOOKER), 1, fptr)) 
                    {
                        if(strcmp(booking.username, name)== 0)
                        {
                            move(row/2+1+2*i, col/2-30);
                            printw("%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s",booking.name,booking.gender,booking.age,booking.type, booking.meal, booking.seat, booking.flightnum, booking.pnr);
                        }
                        i++;
                    }
                    fclose(fptr);
                getch();
                clear();
                goto utils;
                
            }
            else if(choice == 5)
            {
                clear();
                int counter=1;
                printw(">> Hello %s! I am Bandhu, your flight assistant. How can I help you today?\n", name);
                chatting:
                    if(counter>1)
                    printw(">> Is there anything else that I can help you with?\n");
                    greet:
                    int f = chat(name);
                    counter+=1;
                switch(f)
                {
                    case 1: 
                    char pnr[50];
                    printw(">> Cancellation of the tickets requires payment of cancellation charges. Please enter the ticket number that you want to cancel:\n>>");
                    getstr(pnr);
                    cancelBooking(pnr);
                    clear();
                    goto chatting;
                    break;

                    case 0: 
                    char flightnum[50];
                    printw(">> Please enter the flight number which you want to book. I am redirecting you to the booking page!\n>>");
                    getstr(flightnum);
                    clear();
                    bookFlight(flightnum, name);
                    printw("\t\t\tYour ticket has been booked! Press any key to return to chat\n"); 
                    getch();
                    clear();
                    goto chatting;
                    break;

                    case 2: 
                    FILE *fptr;
                    BOOKER booking;
                    fptr = fopen("Booking_List.txt", "r+");
                    if(fptr == NULL)
                    {
                        printw("Error opening file!\n");
                        exit(1);
                    }
                    int i=0;
                    move(row/2-1, col/2-20);
                    printw("The following booking record is found for user:");

                    move(row/2, col/2-30);
                    printw("Name\tGender\tAge\tType\tMeal\tSeat No.\tFlight No.\tTicket No.");
                    while(fread(&booking, sizeof(BOOKER), 1, fptr)) 
                    {
                        if(strcmp(booking.username, name)== 0)
                        {
                            move(row/2+1+2*i, col/2-30);
                            printw("%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s",booking.name,booking.gender,booking.age,booking.type, booking.meal, booking.seat, booking.flightnum, booking.pnr);
                        }
                        i++;
                    }
                    fclose(fptr);

                    getch();
                    clear();
                    goto chatting;
                    break;



                    case 3:printw(">> The maximum baggage limit is 15 kg per person. Extra charges are applicable for baggage beyond 15 kg.\n>> ");
                    goto chatting;
                    break;




                    case 4: printw(">> We offer online payment methods like credit card, debit card, net banking, and UPI. The prices for each flight varies. You have to pay after your seat is booked.\n");
                    goto chatting;
                    break;




                    case 5: printw(">> We offer a variety of meals on board. You can choose from vegetarian and non-vegetarian meals during your booking.\n");
                    goto chatting;
                    break;




                    case 6: printw(">> You can select your seat during the booking process. The availability of seats depends on the flight you choose.\n");
                    goto chatting;
                    break;




                    case 7: printw(">> On cancellation, we refund 40 percent of the total bill amount. Refunds are processed within 7-10 working days. The refund amount will be credited to your account.\n");
                    goto chatting;
                    break;

                    case 8: printw(">> Hello! How can I help you today?\n");
                    goto greet;
                    break;

                    default: printw(">> Thanks! Have a nice day!! Bye...");
                }
                getch();
                clear();
                goto utils;
            }
            else if(choice == 6)
            {
                break;
            }
        }
    }
    if(flag==0)
    {
    move((row/2)-5,(col/2)-3);
    printw("Incorrect Username/Password....." );
    move((row/2)-4,(col/2)-3);
    printw("Login failed, try again.");
    move((row/2)-3,(col/2)-3);
    printw("Press any key to go to main!!");
    fclose(fptr);
    ret:
     return 0;
    }
}
