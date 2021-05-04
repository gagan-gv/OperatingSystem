#include<stdio.h>
#include<stdlib.h>

int mutex = 1, full = 0, empty = 3, y = 0;

int wait(int x){
    return --x;
}

int signal(int x){
    return ++x;
}

void producer(){
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    y++;
    printf("\n\nProducer Produced: %d", y);
    mutex = signal(mutex);
}

void consumer(){
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("\n\nConsumer Consumed: %d", y);
    y--;
    mutex = signal(mutex);
}

void main(){
    int a, flag = 1;
    while(flag){
        printf("\n\nPress 1 to produce.\n\nPress 2 to consume.\n\nPress 3 to exit\n");
        scanf("%d",&a);
        switch(a){
            case 1: 
            if(mutex == 1 && empty != 0){
                producer();
            }else{
                printf("\nBuffer is full");
            }
            break;
            case 2:
            if(mutex == 1 && full != 0){
                consumer();
            }else{
                printf("\nBuffer is empty");
            }
            break;
            case 3:
            exit(0);
            flag = 0;
            break;
        }
    }
}