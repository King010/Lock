#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define SIZE 64

int ring[SIZE];
sem_t blanks,datas;

void *productor(void *arg)
{
	int i=0;
	while(1)
	{
		sem_wait(&blanks);
		int data=rand()%1234;
		ring[i]=data;
		printf("productor done...%d\n",data);
		i++;
		i%=SIZE;
		sem_post(&datas);
		sleep(1);
	}
}

void *consumer(void *arg)
{
	int i=0;
	while(1)
	{
		sem_wait(&datas);
		int data=ring[i];
		printf("consumer done...%d\n",data);
		i++;
		i%=SIZE;
		sem_post(&blanks);
	}
}


int main()
{
	sem_init(&blanks,0,SIZE);
	sem_init(&datas,0,0);
	pthread_t id1,id2;
	pthread_create(&id1,NULL,productor,NULL);
	pthread_create(&id2,NULL,consumer,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	sem_destroy(&blanks);
	sem_destroy(&datas);

	return 0;
}
