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
    int* arg, shmid;
	key_t key2 = 123;
    shmid = shmget(key2, sizeof(int), 0666 | IPC_CREAT);
    arg = (int *)shmat(shmid, NULL, 0);

	(*arg) = atoi(argv[1]);

	int semid;
	key_t key1 = 125;
	struct sembuf mybuf;
	semid = semget(key1 , 1, 0666 | IPC_CREAT);

    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;
    semop(semid, &mybuf, 1);

    key1 = 124;
	semid = semget(key1 , 1, 0666 | IPC_CREAT);

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	semop(semid , &mybuf , 1);
	printf ("%d\n", *arg);
	return 0;
}
