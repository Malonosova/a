#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, char** argv)
{
	int shmid, semid;
	int* arg;

	key_t key1 = 124, key2 = 123;

	struct sembuf mybuf;

	if ((semid = semget(key1 , 2, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can`t get semid\n");
		exit(-1);
	}

	if ((shmid = shmget(key2, sizeof(int), 0666 | IPC_CREAT)) < 0)
	{
		printf("Can't create shared memory\n");
		exit(-1);
	}
	if ((arg = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
	{
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	(*arg) = atoi(argv[1]);

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 1;

	if (semop(semid , &mybuf , 1) < 0)
	{
		printf("Can`t wait for condition\n");
		exit(-1);
	}
	printf ("%d\n", *arg);
	return 0;
}
