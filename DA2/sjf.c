#include<stdio.h>

int main(){
    int burstTime[5],process[5], waitingTime[5], turnAroundTime[5], i, j, n, total = 0, pos, temp, avgWaitingTime, avgTurnAroundTime;
    printf("Enter number of process:");
    scanf("%d",&n);
  
    printf("\nEnter Burst Time: ");
    for(i = 0;i < n;i++){
        printf("\nProcess[%d]:",i+1);
        scanf("%d",&burstTime[i]);
        process[i] = i + 1;         
    }
  
   //sorting of burst times
    for(i = 0;i < n;i++){
        pos = i;
        for(j = i + 1;j < n;j++){
            if(burstTime[j] < burstTime[pos])
                pos = j;
        }
  
        temp = burstTime[i];
        burstTime[i] = burstTime[pos];
        burstTime[pos] = temp;
  
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }
   
    waitingTime[0] = 0;            
  
   
    for(i = 1;i < n;i++){
        waitingTime[i] = 0;
        for(j = 0;j < i;j++)
            waitingTime[i] += burstTime[j];
  
        total += waitingTime[i];
    }
  
    avgWaitingTime = total / n;      
    total = 0;
  
    printf("\nProcess\t\tBurst Time\t\tWaiting Time\tTurnaround Time");
    for(i = 0;i < n;i++){
        turnAroundTime[i] = burstTime[i] + waitingTime[i];   
        total += turnAroundTime[i];
        printf("\nProcess%d\t\t%d\t\t%d\t\t%d", process[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }
  
    avgTurnAroundTime = total / n;    
    printf("\n\nAverage Waiting Time = %d",avgWaitingTime);
    printf("\nAverage Turnaround Time = %d\n",avgTurnAroundTime);
}