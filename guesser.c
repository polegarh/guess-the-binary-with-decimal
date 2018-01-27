#include "assign2Headers.h"

int shouldRun = 1;


void  timeUpHandler(int sig)
{
	 printf("Oh no!  The time is up!");
	 shouldRun=0;
}

void  winHandler(int sig)
{
	 printf("Congratulations!  You found it!\n");
	 shouldRun=0;
}

void  correctHandler(int sig)
{
	printf("Yay!  That was right!\n");
}

void  incorrectHandler(int sig)
{
	printf("Oops!  That was wrong.  Please restart from the beginning.\n");

}

int	main (int argc, char* argv[]){

	struct sigaction  act;
	char guess[LINE_LEN];

	memset(&act,'\0',sizeof(act));
	act.sa_flags		= SA_SIGINFO;
	
	act.sa_handler	= timeUpHandler1;
	sigaction(TIME_OVER_SIGNAL,&act,NULL);

	act.sa_sigaction	= winHandler1;
	sigaction(WIN_SIGNAL,&act,NULL);
  
	act.sa_sigaction	= correctHandler1;
	sigaction(CORRECT_SIGNAL,&act,NULL);

	act.sa_sigaction	= incorrectHandler1;
	sigaction(INCORRECT_SIGNAL,&act,NULL);  
	
	int answererPid = strtoll(argv[1], NULL, 10);
	
	while  (shouldRun)
	{
		printf("What would you like your next guess to be: 0 or 1?");
		fgets(guess, LINE_LEN, stdin);
		int answer = strtoll(guess, NULL, 10);
	    if (answer == 0) 
	    {
			kill (answererPid, ZERO_SIGNAL);
		} 
		else if (answer == 1)
		{
			kill (answererPid, ONE_SIGNAL);
		} 
		else 
		{
			int pid = getpid();
			kill (pid,INCORRECT_SIGNAL);
		}		
		sleep(1);
	}

	printf("guesser finished\n");
	return(EXIT_SUCCESS);
}

