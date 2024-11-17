#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>




// typedef struct {
// 	char name[50];
// 	int age;
// 	char gender[10];
//     char type[10];
//     char meal[20];
//     char pnr[20];
//     char seat[20];
//     char flightnum[20]; //passenger type(adult, child, infant)
// } BOOKER;


// void update_seat_matrix(char* filename, char* airnum, char seats[][10], int size, char* mode)
// {
//     FILE *fptr;
//     int matrixA[10][6], num;
// 	//Accessing file a.txt and storing value in matrixA
// 	fptr = fopen(filename, "r");
// 	for(int i=0; i<10; i++){
// 		for(int j=0; j<6; j++){
// 			fscanf(fptr, "%d", &num);
// 			matrixA[i][j] = num;
// 		}
// 	}
// 	fclose(fptr);

//     if(strcmp(mode, "add")==0)
//     {
//         for(int j=0; j<size; j++)
//         {
//             int row = seats[j][0]-49;
//             int col = seats[j][1] - 'A';
//             matrixA[row][col] = 1;
//         }
//     }
//     else if(strcmp(mode, "remove")==0)
//     {
//         for(int j=0; j<size; j++)
//         {
//             int row = seats[j][0]-49;
//             int col = seats[j][1] - 'A';
//             matrixA[row][col] = 0;
//         }

//     }
    
    

//     fptr = fopen(filename, "w");
//     if (fptr == NULL) {
//         printf("Error opening file %s\n", filename);
//         return;
//     }

//     // Write a 10x6 matrix of random numbers to the file
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 6; j++) {
//             {
//                 // fprintf(fptr, " %d ", rand() % 2);
//                 fprintf(fptr, " %d ", matrixA[i][j]);
//             } // Add a space between numbers
//         }
//         fprintf(fptr, "\n");
//     }

//     // Close the file
//     fclose(fptr);
// }




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
    fptr = fopen("Booking_List.txt", "w");

    char seats[no_of_rec][10];
    int index=-1;
    move(row/2-1, col/2-20);
    printw("The following booking record is found:");
    move(row/2, col/2-20);
    printw("Name\tGender\tAge\tType\tMeal\tSeat No.");
    for(int i=0; i<no_of_rec; i++)
    {   
        if(strcmp(bookings[i].pnr, tick)==0)
        {
            move(row/2+1+i, col/2-20);
            printw("%s\t%s\t%d\t%s\t%s\t%s",bookings[i].name,bookings[i].gender,bookings[i].age,bookings[i].type, bookings[i].meal, bookings[i].seat);
            strcpy(seats[i], bookings[i].seat);
            index=i;
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
            snprintf(filename, sizeof(filename), "/mnt/d/ronit/IISER-K/5 SEM/CS3101/CS3101 project/CS3101_Project/Seat Matrix/%s.txt", bookings[index].flightnum);
            update_seat_matrix(filename, bookings[index].flightnum, seats, sizeof(seats)/sizeof(seats[0]), "remove");

            for(int i=0; i<no_of_rec; i++)
            {
                if(strcmp(bookings[i].pnr, tick)!=0)
                {   
                    fwrite(&bookings[i], sizeof(BOOKER), 1, fptr);
                }
            }
            move(row/2+4+no_of_rec, col/2-20);
            printw("Booking Cancelled Successfully!!\n");
            fileReadWrite("./Seat Matrix/AirList.txt", bookings[index].flightnum, no_of_rec, "remove");
            
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

            
