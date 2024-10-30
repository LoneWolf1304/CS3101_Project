#include <stdio.h>
#include <ncurses.h>
#include<string.h>

int display_name()
{
   
    printw("  _____                                                            _          _   _                      \n");
    printw(" |  __ \\                                                   /\\     (_)        | | (_)                     \n");
    printw(" | |__) |   ___    _ __   __      __   __ _   _   _       /  \\     _   _ __  | |  _   _ __     ___   ___ \n");
    printw(" |  _  /   / _ \\  | '_ \\  \\ \\ /\\ / /  / _` | | | | |     / /\\ \\   | | | '__| | | | | | '_ \\   / _ \\ / __|\n");
    printw(" | | \\ \\  | (_) | | | | |  \\ V  V /  | (_| | | |_| |    / ____ \\  | | | |    | | | | | | | | |  __/ \\__ \\ \n");
    printw(" |_|  \\_\\  \\___/  |_| |_|   \\_/\\_/    \\__,_|  \\__, |   /_/    \\_\\ |_| |_|    |_| |_| |_| |_|  \\___| |___/\n");
    printw("                                               __/ |                                                      \n");
    printw("                                              |___/                                                       \n");
    
    return 0;
}





int main()
{ initscr();
   
    display_name();
    int row, col, choice;
    getmaxyx(stdscr,row,col);
    move(row/2,col/2);
    printw("1. Sign Up\n");
    move((row/2)+1,col/2);
    printw("2. Login \n");
    printw("Enter your choice: ");
    scanw("%d", &choice);
    printw("%d", choice);




    getch();
    endwin();
}