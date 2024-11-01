#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

    move((row/2)-5,(col/2)-3);

    printw("Enter your name: ");
    getstr(user.name);
    move((row/2)-4,(col/2)-3);
    printw("Enter your password: ");
    noecho();
    getstr(user.pwd);
    echo();

    fptr = fopen("Users.txt", "r");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }

    while(fread(&user, sizeof(USER), 1, fptr))
    {
        if(strcmp(user.name, user.name) == 0 && strcmp(user.pwd, user.pwd) == 0)
        {
            move((row/2)-1,(col/2)-3);
            printw("Login successful\n");
            break;
        }
        else
        {
            printw("Login failed. Try Again\n");
            break;
        }
    }
    fclose(fptr);
     return 0;
}