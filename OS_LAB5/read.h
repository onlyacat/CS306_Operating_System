#include<stdio.h>
#include <unistd.h>
#include <time.h>
#include<semaphore.h>
#include<pthread.h>


extern  sem_t db,rc;
extern int readcount;
int firstread = 0;

void *reader(int *buffer){
    if (firstread == 0){
        firstread++;
        usleep(10);
        sem_post(&rc);
    }
    sem_wait(&rc);
    readcount++;
    if (readcount == 1)
        sem_wait(&db);
    sem_post(&rc);
    printf("\nReader Inside..%d\n", *buffer);
    sem_wait(&rc);
    readcount--;
    if (readcount == 0)
        sem_post(&db);
    sem_post(&rc);
}
