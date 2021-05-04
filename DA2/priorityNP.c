#include<stdio.h>
 
int main(){
    int burstTime[5], process[5], waitingTime[5], turnAroundTime[5], priority[5];
    int i, j, n, total = 0, position, temp;
    int avgWaitingTime, avgTurnAroundTime;
    printf("Enter number of Processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time and Priority For %d Processes\n", n);
    for(i = 0; i < n; i++){
        printf("Process[%d]\n", i + 1);
        printf("Process Burst Time: ");
        scanf("%d", &burstTime[i]);
        printf("Process Priority: ");
        scanf("%d", &priority[i]);
        process[i] = i + 1;
    }
    for(i = 0; i < n; i++){
        position = i;
        for(j = i + 1; j < n; j++){
            if(priority[j] < priority[position]){
                position = j;
            }
        }
        temp = priority[i];
        priority[i] = priority[position];
        priority[position] = temp; 
        temp = burstTime[i];
        burstTime[i] = burstTime[position];
        burstTime[position] = temp;
        temp = process[i];
        process[i] = process[position];
        process[position] = temp;
    }
    waitingTime[0] = 0;
    for(i = 1; i < n; i++)
    {
        waitingTime[i] = 0;
        for(j = 0; j < i; j++)
        {
            waitingTime[i] = waitingTime[i] + burstTime[j];
        }
        total += waitingTime[i];
    }
    avgWaitingTime = total / n;
    total = 0;
    printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
    for(i = 0; i < n; i++)
    {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
        total += turnAroundTime[i];
        printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }
    avgTurnAroundTime = total / n;
    printf("\n\nAverage Waiting Time: %d", avgWaitingTime);
    printf("\nAverage Turnaround Time: %d\n", avgTurnAroundTime);
    return 0;
}