#include <stdio.h>
<<<<<<< HEAD
#include <unistd.h>
int main(int argc, char **argv){
	int pid , i = 0, k;
	char buffer[100];
	scanf ("%d",&pid);

=======
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
void sighand (int signo){

	printf("received signal\n");

	return;
}
int main(int argc, char **argv){
	int pid , i = 0, k, sig;
	char buffer[100];
	sigset_t wait;
	
	sigemptyset(&wait);
	sigaddset(&wait, SIGINT);

	printf("pid is %d\n",k = getpid());
	scanf ("%d",&pid);

	signal(SIGUSR2,sighand);
	
>>>>>>> 5b124fa6c721ddc495b82b5caee56e94efa0122b
	while ( 0 == 0 ){
		scanf("%c",buffer);
		while( buffer[i]  != '\n'){
			
			i++;
			scanf("%c",&buffer[i]);
			
		}
	
		buffer[i + 1] = 0;		
		
<<<<<<< HEAD
=======
		printf("end of scanf\n");
>>>>>>> 5b124fa6c721ddc495b82b5caee56e94efa0122b

		while ( i >= 0) {
	
			for(k = 0 ; k < 8; k++){
<<<<<<< HEAD
			
				if (*buffer % 2 == 0)
					kill(pid , SIGINT);
				else 
					kill(pid , SIGILL);
			
				*buffer /= 2;

				usleep(1000);
=======

				kill(pid , SIGUSR1);
			
				printf("starting desintegration\n");

				if (*buffer % 2 == 0){
					kill(pid , SIGINT);
					printf("0 sent\n");
				}
				else {
					kill(pid , SIGILL);
					printf("1 sent\n");
				}		
				
				buffer[0] /= 2;

				printf("in process\n");

				if (k = sigsuspend(&wait) == -1)
					exit(1);

				printf("ending desintegration\n");
>>>>>>> 5b124fa6c721ddc495b82b5caee56e94efa0122b
	
			}
			
			for(k = 0; k < i; k++){
		
				buffer[k] = buffer[k + 1];
			}

<<<<<<< HEAD
			usleep(1000);
		
=======
>>>>>>> 5b124fa6c721ddc495b82b5caee56e94efa0122b
			i--;
			
		}

		i = 0;

	}

	
	return 0;
}
