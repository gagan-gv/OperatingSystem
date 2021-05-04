#include<stdio.h>
 
struct process
{
    char processName;
    int arrivalTime, burstTime, ct, waitingTime, turnAroundTime, priority;
    int status;
}processQueue[5];
 
int n;
 
void ArrivalTimeSorting()
{
    struct process temp;
    int i, j;
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(processQueue[i].arrivalTime > processQueue[j].arrivalTime)
            {
                temp = processQueue[i];
                processQueue[i] = processQueue[j];
                processQueue[j] = temp;
            }
        }
    }
}
 
int main()
{
    int i, time = 0, burstTime = 0, largest;
    char c;
    float waitingTime = 0, turnAroundTime = 0, avgWaitingTime, avgTurnAroundTime;
    printf("\nEnter Total Number of Processes:\t");
    scanf("%d", &n);
    for(i = 0, c = 'A'; i < n; i++, c++)
    {
        processQueue[i].processName = c;
        printf("\nEnter Details For Process[%C]:\n", processQueue[i].processName);
        printf("Enter Arrival Time:\t");
        scanf("%d", &processQueue[i].arrivalTime );
        printf("Enter Burst Time:\t");
        scanf("%d", &processQueue[i].burstTime);
        printf("Enter Priority:\t");
        scanf("%d", &processQueue[i].priority);
        processQueue[i].status = 0;
        burstTime += processQueue[i].burstTime;
    }
    ArrivalTimeSorting();
    processQueue[4].priority = -9999;
    printf("\nProcess Name\tArrival Time\tBurst Time\tPriority\tWaiting Time");
    for(time = processQueue[0].arrivalTime; time < burstTime; time++)
    {
        largest = 4;
        for(i = 0; i < n; i++)
        {
            if(processQueue[i].arrivalTime <= time && processQueue[i].status != 1 && processQueue[i].priority > processQueue[largest].priority)
            {
                largest = i;
            }
        }
        time += processQueue[largest].burstTime;
        processQueue[largest].ct = time;
        processQueue[largest].waitingTime = processQueue[largest].ct - processQueue[largest].arrivalTime - processQueue[largest].burstTime;
        processQueue[largest].turnAroundTime = processQueue[largest].ct - processQueue[largest].arrivalTime;
        processQueue[largest].status = 1;
        waitingTime = waitingTime + processQueue[largest].waitingTime;
        turnAroundTime = turnAroundTime + processQueue[largest].turnAroundTime;
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d", processQueue[largest].processName, processQueue[largest].arrivalTime, processQueue[largest].burstTime, processQueue[largest].priority, processQueue[largest].waitingTime);
    }
    avgWaitingTime = waitingTime / n;
    avgTurnAroundTime = turnAroundTime / n;
    printf("\n\nAverage waiting time:\t%f\n", avgWaitingTime);
    printf("Average Turnaround Time:\t%f\n", avgTurnAroundTime);
    return 0;
}