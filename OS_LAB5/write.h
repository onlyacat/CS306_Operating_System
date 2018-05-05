#include<stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include<semaphore.h>
#include<pthread.h>


sem_t db,rc;
int readcount;
int firstwrite = 0;

void *writer(int *buffer){
    if (firstwrite == 0){
        firstwrite++;
        sem_post(&db);
    }
    sem_wait(&db);
    (*buffer)++;
    printf ("write ::%d\n", *buffer);
    sem_post(&db);
}
