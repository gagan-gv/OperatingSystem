#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define buffersize 100

pthread_mutex_t mutex;
pthread_t producerThread[100], consumerThread[100];
sem_t full,empty;
int counter;
int buffer[buffersize];

void initialize(){
    pthread_mutex_init(&mutex,NULL);
    sem_init(&full,1,0);
    sem_init(&empty,1,buffersize);
    counter=0;
}
void write(int item){
    buffer[counter++]=item;
}
int read(){
    return(buffer[--counter]);
}
void *producer (void *produce){
    int waittime,item,i;
    item=rand()%5;
    waittime=rand()%5;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("\nProducer produced: %d\n",item);
    write(item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}
void *consumer(void *consume){
    int waittime,item;
    waittime=rand()%5;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    item=read();
    printf("\nConsumer consumed: %d\n",item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}
void main(){
    int producers, consumers, i;
    initialize();
    printf("\nEnter the number of producers: ");
    scanf("%d",&producers);
    printf("\nEnter the number of consumers: ");
    scanf("%d",&consumers);
    for(i = 0;i < producers;i++){
        pthread_create(&producerThread[i],NULL,producer,NULL);
    }
    for(i=0;i<consumers;i++){
        pthread_create(&consumerThread[i],NULL,consumer,NULL);
    }
    for(i=0;i<producers;i++){
        pthread_join(producerThread[i],NULL);
    }
    for(i=0;i<consumers;i++){
        pthread_join(consumerThread[i],NULL);
    }
}