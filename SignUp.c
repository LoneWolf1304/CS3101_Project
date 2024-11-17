#include <stdio.h>
#include <string.h>
#include <stdlib.h>




typedef struct user{
char name[50];
char pwd[50];
}USER;

typedef struct admin{
char name[50];
char pwd[50];
char id[50];
}ADMIN;


void fileWrite(char *filename, USER *user)
{
    FILE *fptr;
    fptr = fopen(filename, "a");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    fwrite(user, sizeof(USER), 1, fptr);
    fclose(fptr);
}


void fileWrite1(char *filename, ADMIN *admin)
{
    FILE *fptr;
    fptr = fopen(filename, "a");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    fwrite(admin, sizeof(ADMIN), 1, fptr);
    fclose(fptr);
}

void fileRead(char *filename)
{
    FILE *fptr;
    USER user;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    while(fread(&user, sizeof(USER), 1, fptr))
    {
        printw("Name: %s\n", user.name);
        printw("Password: %s\n", user.pwd);
    }
    fclose(fptr);
}

void fileRead1(char *filename)
{
    FILE *fptr;
    ADMIN admin;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    while(fread(&admin, sizeof(ADMIN), 1, fptr))
    {
        printw("Name: %s\n", admin.name);
        printw("Password: %s\n", admin.pwd);
        printw("ID: %s\n", admin.id);
    }
    fclose(fptr);
}





int sign_up()
{
    USER user;
    ADMIN admin;
    char pwc[50], acc_typ[50], id[50];
    int row, col, choice;
    char nm[50], pwd[50];
    char filename[] = "Users.txt";
    char filename1[] = "Admins.txt";
    getmaxyx(stdscr,row,col);
    move((row/2)-7,(col/2)-4);
    printw("New User Details");
    move((row/2)-2,(col/2)-4);
    printw("Enter account type (User/Admin): ");
    getstr(acc_typ);
    

    clear();
    move((row/2)-7,(col/2)-4);
    printw("New User Details");
    
    if (strcmp(acc_typ, "Admin") == 0)
    {
        move((row/2)-7,(col/2)-4);
    printw("New Admin Details");
        move((row/2)-4,(col/2)-4);
        printw("Enter your name: ");
        getstr(admin.name);
        move((row/2)-3,(col/2)-4);
        printw("Enter Ronway ID: ");
        getstr(admin.id);
        move((row/2)-2,(col/2)-4);
        printw("Enter your password: ");
        noecho();
        getstr(admin.pwd);
        move((row/2)-1,(col/2)-4);
        printw("Confirm password: ");
        getstr(pwc);
        echo();
        if(strcmp(admin.pwd, pwc) == 0)
        {
        fileWrite1(filename1, &admin);
        int row, col, choice;
        getmaxyx(stdscr,row,col);
        move((row/2)+2,(col/2)-15);
        printw("Sign-Up Successful....Welcome to Ronway Airlines, %s!", admin.name);
        }
        else
        {
        move((row/2)+2,(col/2)-4);
        printw("Sorry! Passwords do not match...Sign-Up Again!");
        }

    }
    else
    {
        move((row/2)-7,(col/2)-4);
    printw("New User Details");
    move((row/2)-3,(col/2)-4);
    printw("Enter your name: ");
    getstr(user.name);
    move((row/2)-2,(col/2)-4);
    printw("Enter your password: ");
    // scanf("%s", user.pwd);
    //fgets(user.pwd, 50, stdin);
    noecho();
    getstr(user.pwd);
    move((row/2)-1,(col/2)-4);
    printw("Confirm password: ");
    getstr(pwc);
    echo();
    if(strcmp(user.pwd, pwc) == 0)
    {
    fileWrite(filename, &user);
    int row, col, choice;
    getmaxyx(stdscr,row,col);
    move((row/2)+2,(col/2)-15);
    printw("Signup Successful....Welcome to Ronway Airlines, %s!", user.name);
    }
    else
    {
    move((row/2)+2,(col/2)-4);
    printw("Sorry! Passwords do not match");
    }
    }
    return 0;
}




