#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int buffer = 0, flip = 0;
void sighand (int signo){

        printf("received signal\n");

        return;
}
void sighandler (int signo){
	
	buffer *= 2;

	printf("received 0\n");

	return;
}
void sighandler1 (int signo) {

	buffer *= 2;
	
	buffer += 1;

	printf("received 1\n");

	return;
}
int main(int argc, char **argv){
	int pid , k;
	char i = 0;
	sigset_t wait;
	sigemptyset(&wait);
	sigaddset(&wait , SIGINT);
	sigaddset(&wait , SIGILL);

	printf("pid is %d\n",k = getpid());
	scanf("%d",&pid);
	
	signal(SIGINT , sighandler);
	signal(SIGILL , sighandler1);
	signal(SIGUSR1,sighand);

	
	while(0 == 0){

		for (k = 0; k < 8; k ++){
			printf("start of receiving\n");
			sigsuspend(&wait);
			printf("bit received\n");
			usleep(9999);
//			sigsuspend(&wait);
			kill(pid, SIGUSR2);

		}
		printf("end of receiving\n");

		for(k = 0; k < 8; k ++){
			i *= 2;
			i += buffer % 2;
			buffer /= 2;
			
		}
		printf("%c",i);
		i = 0;	
		buffer = 0;	
	}
		return 0;
}
