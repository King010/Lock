#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int buf;
pthread_rwlock_t rwlock;


void *my_read(void *arg)
{
	while(1){
	int ret;
	if((ret=pthread_rwlock_tryrdlock(&rwlock))!=0)
	{
		printf("writer is writing\n");
		continue;
	}
	else
	{
		printf("reader number is:%d\n",buf);
		pthread_rwlock_unlock(&rwlock);
	}
	sleep(1);
	}
	return NULL;
}

void *my_write(void *arg)
{
	while(1){
	int ret;
	if((ret=pthread_rwlock_trywrlock(&rwlock))!=0)
	{
		printf("reader is reading\n");
		continue;
	}
	else
	{
		buf++;
		printf("writer write number is:%d\n",buf);
		pthread_rwlock_unlock(&rwlock);
	}
	sleep(1);
	}
	return NULL;
}


int main()
{
	pthread_rwlock_init(&rwlock,NULL);
	pthread_t id1;
	pthread_t id2;
	pthread_create(&id1,NULL,my_read,NULL);
	pthread_create(&id2,NULL,my_write,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
