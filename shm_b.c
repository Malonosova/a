
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>

int main() {
	int semid;
	key_t key1 = 125;
	struct sembuf mybuf;
	semid = semget(key1 , 1, 0666 | IPC_CREAT);
    mybuf.sem_op = -1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;
    semop(semid, &mybuf, 1);

    key1 = 124;
	semid = semget(key1 , 1, 0666 | IPC_CREAT);

    int* arg, shmid;
	key_t key2 = 123;
    shmid = shmget(key2, sizeof(int), 0666 | IPC_CREAT);
    arg = (int *)shmat(shmid, NULL, 0);
    *arg = (*arg) * (*arg);
	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	semop(semid , &mybuf , 1);
	return 0;
}
