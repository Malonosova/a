#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int k;

void k_1()
{
	k = 1;
	return;
}

void k_2()
{
	k = 2;
	return;
}

int main()
{
	int tr_pid, flag = 0, out = 0;
	k = 0;

	signal(SIGUSR1, k_1);
	signal(SIGUSR2, k_2);

	printf("Reciever PID is: %i\n", getpid());
	scanf("%i", &tr_pid);

	while(1)
	{
		while(1)
		{
			switch(k)
			{
				case 0:
					break;
/*				case 1:
					out >>= 1;
					flag++;
					k = 0;
					kill(tr_pid, SIGUSR1);
					break;
				case 2:
					out >>= 1;
					out |= (1 << 7);
					flag++;
					k = 0;
					kill(tr_pid, SIGUSR1);
					break;
*/				default:
					out = (out >> 1);
					out = (out | (((k + 1) % 2) << 7));
					flag++;
					k = 0;
					kill(tr_pid, SIGUSR1);
					break;
			}
			if(flag == 8) break;
		}

	printf("%c", (char)out);
	if (((char)out) == '$')
	{
		kill(tr_pid, SIGUSR2);
		break;
	}
	out = 0;
	flag = 0;
	}

	return 0;
}
