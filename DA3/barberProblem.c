#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int seats[2];
int customers[2];
int barber[2];
int freeSeats[2];

void randomWait() {
   int delay;
   delay = random() % 99;
   printf("  - wait: %d\n", delay); 
}

void barberProcess() {
    int i; 
    int num;
    for (i = 1; i <= 10; ++i) {
        printf("Barber %d is trying to get a customer\n",i);
        P(customers); 
        printf("Barber %d is waiting for the seat to become free\n",i);
        P(seats); 
        read(freeSeats[0],&num,sizeof(int));
        num++; 
        write(freeSeats[1],&num,sizeof(int));
        printf("Barber %d is increasing the number of free accessSeats to %d\n",i,num);
        V(barber); 
        V(seats); 
        printf("Barber is now cutting hair %d\n",i);
        randomWait();	
    }
}

void customerProcess() {
    int i;
    int num;
    for (i = 1; i <= 2; ++i) {
        printf("New customer trying to find a seat\n");
        P(seats); 
        read(freeSeats[0],&num,sizeof(int));
        if (num > 0) {
            num--;
            write(freeSeats[1],&num,sizeof(int));
            printf("Customer left seating in waiting room. The total free accessSeats are now: %d\n",num);
            V(customers); 
            V(seats); 
            printf("Customer is now waiting for the barber\n");
            P(barber); 
            printf("Customer is now getting a hair cut\n");
        }else{
            write(freeSeats[1],&num,sizeof(int));
            V(seats); 
            printf("No free chairs available\n");
        }
        randomWait();
    }
}
void V(int arr[]) {
    int a=1;
    write(arr[1],&a,sizeof(int));
}

void P(int arr[]) {
    int a;
    read(arr[0],&a,sizeof(int));
}

void main() {
    int i;
    pipe(seats);
    pipe(customers);
    pipe(barber);
    pipe(freeSeats); 
        
    V(seats); 
        
    int num = 3; 
    write(freeSeats[1],&num,sizeof(int));
        
    if (fork() == 0) {
        srand(time(0)+1); 
        barberProcess();
        return;
    }
    
    for (i = 1; i <= 5; i++) { 
        if (fork() == 0) {
            srand(time(0)+2*i);
            customerProcess();
            return;
        }
    }
    sleep(10);
}