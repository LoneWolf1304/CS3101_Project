#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct user{
char name[50];
char pwd[50];
}USER;


void fileWrite(char *filename, USER *user )
{
    FILE *fptr;
    fptr = fopen(filename, "w");
    if(fptr == NULL)
    {
    printw("Error opening file!\n");
    exit(1);
    }
    fwrite(user, sizeof(USER), 1, fptr);
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
    fread(&user, sizeof(USER), 1, fptr);
    printw("Name: %s\n", user.name);
    printw("Password: %s\n", user.pwd);
    
    fclose(fptr);
}



int sign_up()
{
    USER user;
    char nm[50], pwd[50];
    char filename[] = "Users.txt";
    printw("Enter your name: ");
    getstr(user.name);
    printw("Enter your password: ");
    // scanf("%s", user.pwd);
    //fgets(user.pwd, 50, stdin);
    getstr(user.pwd);
    fileWrite(filename, &user);
    fileRead(filename);
    return 0;
}




