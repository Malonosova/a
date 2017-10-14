#include <stdio.h>

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
	task_t * vart= (task_t*)var;
	int frag = 0, k = vart->id;
	long long unsigned worker =vart->worker;
	while(k <= TASK_N){

		pthread_mutex_lock(&lock);
		while(vart->status != NEW){
			var += sizeof(task_t);
			k++;
			vart = (task_t*)var;
		}

		vart->status = PROCESSING;

		pthread_mutex_unlock(&lock);
		if (k >= TASK_N){

			break;
		}
		printf("Task %d is putting thread No %llu to sleep for %d mks\n", vart->id, worker, *((int*)var));

		usleep(*((int*)var));
		frag++;

		pthread_mutex_lock(&lock);
		vart->status = DONE;
		pthread_mutex_unlock(&lock);


	}
	printf("Worker %llu has fragged %d tasks\n",worker,frag);
	return NULL;
}
int main(){
	statuses status;
	int result , i;
	void* arg[2];
	for (i = 0; i < TASK_N; i++){
		tasks[i].id = i;
		tasks[i].duration = abs(random() % 1000);
	}

	for (i = 0; i < THREAD_N; i++){
		pthread_create(&(tasks[i].worker), NULL, my_thread, (void*)(tasks));
	}
	for(i = 0; i < THREAD_N; i++){
		pthread_join((tasks[i].worker),NULL);
	}

	printf("END\n");

	pthread_mutex_destroy(&lock);
	return 0;
}
