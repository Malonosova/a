#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#define TASK_N 100
#define THREAD_N 10

typedef enum{
	NEW,
	PROCESSING,
	DONE
}statuses;
typedef struct{
	int duration;
	int id;
	statuses status;
	pthread_t worker;
} task_t;

pthread_mutex_t lock;
task_t tasks[TASK_N];

void* my_thread(void* var){
	int frag = 0, k = *((int*)(var + 4));
	long long unsigned worker = *((pthread_t*)(var + 8 + sizeof(statuses)));
	while(k <= TASK_N){

		pthread_mutex_lock(&lock);
		while((*(statuses*)(var + 8)) != NEW /*&& k < TASK_N*/){
			var += sizeof(task_t);
			k++;
		}

		*((statuses*)(var + 8)) = PROCESSING;
		
		pthread_mutex_unlock(&lock);
		if (k >= TASK_N){

			break;
		}
		printf("Task No %d is putting thread No %llu to sleep for %d mks\n",*((int*)(var + 4)), worker, *((int*)var));
		
		usleep(*((int*)var));
		frag++;

		pthread_mutex_lock(&lock);
		*((statuses*)(var + 8)) = DONE;
		pthread_mutex_unlock(&lock);


	}
	printf("Worker No %llu has fragged %d tasks\n",worker,frag);
	return NULL;
}
int main(){
	statuses status;
	pthread_t thread_id[THREAD_N];
	int result , i;

	for (i = 0; i < TASK_N; i++){
		tasks[i].id = i;
		tasks[i].duration = abs(random() % 1000);
	}

	for (i = 0; i < THREAD_N; i++){
		pthread_create(&(tasks[i].worker), NULL, my_thread, (void*)(&(tasks[i])));
	}
	for(i = 0; i < THREAD_N; i++){
		pthread_join(tasks[i].worker,NULL);
	}

	printf("END\n");

	pthread_mutex_destroy(&lock);

	return 0;
}