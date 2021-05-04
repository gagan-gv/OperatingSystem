#include<stdio.h>
 
#define n 5
 
int compltedDinner = 0,i;
 
struct chopSticks{
	int inUse;
}CSAvailability[n];
 
struct philosp{
	int left;
	int right;
}status[n];
 
void toDine(int philosopherNo){
	if(status[philosopherNo].left==10 && status[philosopherNo].right==10){
        printf("Philosopher %d completed his dinner\n",philosopherNo+1);
    }
	else if(status[philosopherNo].left==1 && status[philosopherNo].right==1){
            printf("Philosopher %d completed his dinner\n",philosopherNo+1);
            status[philosopherNo].left = status[philosopherNo].right = 10;
            int otherChopStick = philosopherNo-1;
            if(otherChopStick== -1){
                otherChopStick=(n-1);
            }
            CSAvailability[philosopherNo].inUse = CSAvailability[otherChopStick].inUse = 0;
            printf("Philosopher %d has used chopsticks %d and %d\n",philosopherNo+1,philosopherNo+1,otherChopStick+1);
            compltedDinner++;
        }
        else if(status[philosopherNo].left==1 && status[philosopherNo].right==0){
                if(philosopherNo==(n-1)){
                    if(CSAvailability[philosopherNo].inUse==0){
                        CSAvailability[philosopherNo].inUse = status[philosopherNo].right = 1;
                        printf("Philosopher %d is using chopstick %d\n",philosopherNo+1,philosopherNo+1);
                    }else{
                        printf("Philosopher %d is waiting for chopstick %d\n",philosopherNo+1,philosopherNo+1);
                    }
                }else{
                    int temp = philosopherNo;
                    philosopherNo-=1;
 
                    if(philosopherNo== -1){
                        philosopherNo=(n-1);
                    }
 
                    if(CSAvailability[philosopherNo].inUse == 0){
                        CSAvailability[philosopherNo].inUse = status[temp].right = 1;
                        printf("Philosopher %d is using chopstick %d\n",temp+1,philosopherNo+1);
                    }else{
                        printf("Philosopher %d is waiting for chopstick %d\n",temp+1,philosopherNo+1);
                    }
                }
            }
            else if(status[philosopherNo].left==0){
                    if(philosopherNo==(n-1)){
                        if(CSAvailability[philosopherNo-1].inUse==0){
                            CSAvailability[philosopherNo-1].inUse = status[philosopherNo].left = 1;
                            printf("Philosopher %d is using chopstick %d\n",philosopherNo,philosopherNo+1);
                        }else{
                            printf("Philosopher %d is waiting for chopstick %d\n",philosopherNo+1,philosopherNo);
                        }
                    }else{ //except last philosopher case
                        if(CSAvailability[philosopherNo].inUse == 0){
                            CSAvailability[philosopherNo].inUse = status[philosopherNo].left = 1;
                            printf("Philosopher %d is using chopstick %d\n",philosopherNo+1,philosopherNo+1);
                        }else{
                            printf("Philosopher %d is waiting for chopstick %d\n",philosopherNo+1,philosopherNo+1);
                        }
                    }
        }
}
 
void main(){
	for(i=0;i<n;i++)
        CSAvailability[i].inUse=status[i].left=status[i].right=0;
 
	while(compltedDinner<n){
		for(i=0;i<n;i++)
            toDine(i);
		printf("\nNumber of philosophers completed dinner = %d\n\n",compltedDinner);
	}
}