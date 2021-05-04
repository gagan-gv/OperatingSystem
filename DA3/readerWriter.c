#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex, writeBlock;
int data = 0, readCount = 0;

void *reader(void *read){
    int x = ((int) read);
    sem_wait(&mutex);
    readCount++;
    if(readCount == 1){
        sem_wait(&writeBlock);
    }
    sem_post(&mutex);
    printf("\nData is read by reader %d is %d\n", x, data);
    sleep(1);
    sem_wait(&mutex);
    readCount--;
    if(readCount == 0){
        sem_post(&writeBlock);
    }
    sem_post(&mutex);
}

void *writer(void *write){
    int x = ((int) write);
    sem_wait(&writeBlock);
    data++;
    printf("\nData is writen by the writer %d is %d\n",x,data);
    sleep(1);
    sem_post(&writeBlock);
}

void main(){
    pthread_t readThread[5], writeThread[5];
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    for (int i = 0; i < 5; i++){
        pthread_create(&writeThread[i], NULL, writer, (void *)i);
        pthread_create(&readThread[i], NULL, reader, (void *)i);
    }
    
    for(int i = 0; i < 5; i++){
        pthread_join(writeThread[i], NULL);
        pthread_join(readThread[i], NULL);
    }
}