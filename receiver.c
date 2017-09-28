#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
char buffer = 0, flip = 0;
void sighandler (int signo) {

	flip = 1;
	
	buffer *= 2;

	return;
}
void sighandler1 (int signo) {
	
	flip = 1;

	buffer += 1;
	
	buffer *= 2;

	return;
}
int main(int argc, char **argv){
	int pid , i = 0, k;
	char input;
	printf("pid is %d\n",pid = getpid());
	scanf("%d",&pid);
	
	signal(SIGINT , sighandler);
	signal(SIGILL , sighandler1);
	
	while(0 == 0){
		
		if( flip == 1 ){

			for (k = 0; k < 8; k ++){
				sleep(1);

			}
		
			for(k = 0; k < 8; k ++){
				i = buffer % 2;
				buffer /= 2;
				buffer += i * 128;
			}

			printf("%u",buffer);
			buffer = 0;	

			flip = 0;
		}
		
		sleep(1);
		printf("\n");
		
	}
	
	
	
	return 0;
}
