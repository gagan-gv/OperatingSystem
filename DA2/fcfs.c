#include<stdio.h>
 
int main(){
    int n, burstTime[5], waitingTime[5], turnAroundTime[5], avgWaitingTime = 0, avgTurnAroundTime = 0, i, j;
    printf("Enter total number of processes:");
    scanf("%d",&n);
 
    printf("\nEnter Process Burst Time\n");
    for(i = 0; i < n; i++){
        printf("Process[%d]:",i+1);
        scanf("%d",&burstTime[i]);
    }
 
    waitingTime[0] = 0;   
 
    for(i = 1; i < n; i++){
        waitingTime[i] = 0;
        for(j = 0; j < i; j++)
            waitingTime[i] += burstTime[j];
    }
 
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
 
    for(i=0;i<n;i++){
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
        avgWaitingTime += waitingTime[i];
        avgTurnAroundTime += turnAroundTime[i];
        printf("\nProcess[%d]\t\t%d\t\t%d\t\t%d",i+1, burstTime[i], waitingTime[i], turnAroundTime[i]);
    }
 
    avgWaitingTime /= n;
    avgTurnAroundTime /= n;

    printf("\n\nAverage Waiting Time:%d", avgWaitingTime);
    printf("\nAverage Turnaround Time:%d\n", avgTurnAroundTime);
 
    return 0;
}