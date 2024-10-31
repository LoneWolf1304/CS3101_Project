#include <stdio.h>
#include <ncurses.h>
#include<string.h>
#include "SignUp.c"
int display_name()
{
    move(0, 13);
    printw("  _____                                                            _          _   _                      \n");
    move(1, 13);
    printw(" |  __ \\                                                   /\\     (_)        | | (_)                     \n");
    move(2, 13);
    printw(" | |__) |   ___    _ __   __      __   __ _   _   _       /  \\     _   _ __  | |  _   _ __     ___   ___ \n");
    move(3, 13);
    printw(" |  _  /   / _ \\  | '_ \\  \\ \\ /\\ / /  / _` | | | | |     / /\\ \\   | | | '__| | | | | | '_ \\   / _ \\ / __|\n");
    move(4, 13);
    printw(" | | \\ \\  | (_) | | | | |  \\ V  V /  | (_| | | |_| |    / ____ \\  | | | |    | | | | | | | | |  __/ \\__ \\ \n");
    move(5, 13);
    printw(" |_|  \\_\\  \\___/  |_| |_|   \\_/\\_/    \\__,_|  \\__, |   /_/    \\_\\ |_| |_|    |_| |_| |_| |_|  \\___| |___/\n");
    move(6, 13);
    printw("                                               __/ |                                                      \n");
    move(7, 13);
    printw("                                              |___/                                                       \n");
    return 0;
}


int main()
{ initscr();
   
    display_name();
    int row, col, choice;
    getmaxyx(stdscr,row,col);
    //printw("%d, %d", row, col);
    move((row/2)-8,(col/2)-20);

    printw("Where the sky's not the limit, but just the view!\n");
    move((row/2)-5,(col/2)-3);
    refresh();
    printw("1. Sign Up\n");
    move((row/2)-4,(col/2)-3);
    printw( "2. Login \n");
    move((row/2)-1,(col/2)-3);
    printw("Enter your choice: ");
    scanw("%d", &choice);
    system("clear"); 
    //printw("%d", choice);
    switch(choice)
    {
        case 1:  
                sign_up();
                break;
        case 2: printw("Login");
                break;
        default: printw("Invalid choice");
    }




    getch();
    endwin();
}