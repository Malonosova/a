#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char **argv){
	long long int start , finish, sum = 0;
	int shag, numfork , k , p, i;
	int pipe_fd[100];
	char buffer[10];
	numfork = atoi(argv[1]);
	start = atoll(argv[2]);
	finish = atoll(argv[3]);

	shag = (finish - start + 1) / numfork;
	
	for(i = 0; i < numfork; i++){

		if (k = pipe(&pipe_fd[2*i]) < 0 ){
			printf("pipe failed");
			exit(1);
		}
	
		p = fork();

		if ( p < 0){
			printf("fork failed");
			exit(1);
		}

		if (p == 0){
			for (k = start; k < start + shag; k++){
				sum+=k;	
			}
			printf("child number %d have %llu\n",i,sum);
			sprintf(buffer,"%lld",sum);
			write(pipe_fd[2*i+1] , buffer , 10);
			return 0;
		}

		start+=shag;
	}
	if (numfork != 1){// && (((finish - start + 1) % numfork) != 0)){
		i = start;
		while (i <= finish){
			sum+=i;
			i++;	
		}
	}

	for(i = 0; i < numfork; i++)
		{
			read(pipe_fd[2*i] , &buffer, 10);
			sum += atoll(buffer);
			}

	printf("sum is %lld\n",sum);

	
	return 0;
}
