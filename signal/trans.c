#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int k, end;

void k_1()
{
	k = 1;
	return;
}

void is_end()
{
	end = 1;
	return;
}
int main()
{
	int rec_pid, i;
	char inp;

	k = 0;

	signal(SIGUSR1, k_1);
	signal(SIGUSR2, is_end);

	printf("Transmitter PID is: %i\n", getpid());
	scanf("%i\n", &rec_pid);

	while(!end)
	{
		scanf("%c", &inp);

		for(i = 0; i < 8; i++)
		{
			if((inp % 2) == 0) kill(rec_pid, SIGUSR1);
			else kill(rec_pid, SIGUSR2);
			inp = (inp >> 1);
			while(1)
				if(k)
					break;
			k = 0;
		}
	}

	return 0;
}
