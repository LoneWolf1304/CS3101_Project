#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<ncurses.h>

char *lowering(char *str)
{
    for(int i=0;i<strlen(str);i++)
    {
        str[i]=tolower(str[i]);
    }
    return str;
}


int indexOf(char *str[200], char substr[], int s)
{
    int i;
     for(i=0; i<s; i++)
     {
         if(strcmp(str[i],substr)==0)
         {
             return i;
         }
     }
     return -1;
}

int chat(char *name)
{
    //while(1)
    {
        char response[200];
        char *ptr;
        char *keywords[200];
        int i=0;
        getstr(response);

        ptr=strtok(response," ");
        while(ptr!=NULL)
        {
            //printf("%s\n",ptr); 
            keywords[i]=lowering(ptr);
            ptr=strtok(NULL," ");
            i++;
        }
        int num = indexOf(keywords, "how", sizeof(keywords)/sizeof(keywords[0]));
        if(num>-1)
        {
            num = indexOf(keywords, "book", sizeof(keywords)/sizeof(keywords[0]));
            if(num>-1)
                return 2;
            num = indexOf(keywords, "cancel", sizeof(keywords)/sizeof(keywords[0]));
             if(num>-1)
                return 1;
        }
    }
}



