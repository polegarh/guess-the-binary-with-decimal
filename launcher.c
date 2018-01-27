#include "assign2Headers.h"

int answererPid;
int guesserPid;
int shouldRun = 1;

void  sigAlrmHandler(int sig)
{
    kill(answererPid,TIME_OVER_SIGNAL);
    kill(guesserPid,TIME_OVER_SIGNAL);
    shouldRun=0;
}

void  sigChldHandler(int sig)
{
	wait(NULL);
	shouldRun = 0;
}

int main(void){

	struct sigaction act;
    memset(&act, '\0', sizeof(act));
    
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	
    act.sa_handler = sigAlrmHandler;
    sigaction(SIGALRM, &act, NULL);

    act.sa_handler = sigChldHandler;
    sigaction(SIGCHLD, &act, NULL);


	char line[LINE_LEN];
	
	answererPid = fork();

	if(answererPid == 0)
	{
        execl(ANSWERER_PROGNAME,ANSWERER_PROGNAME, NULL);
		exit(0);
    }
	guesserPid = fork();
	if(guesserPid == 0)
	{
        snprintf(line,LINE_LEN,"%d",answererPid);
        execl(GUESSER_PROGNAME,GUESSER_PROGNAME,line, NULL);
        exit(0);
	}
    alarm(NUM_SECONDS);
    while(shouldRun)
    {
        sleep(1);
    }
    sleep(1);
    sleep(1);
    printf("launcher finished\n");
    return (EXIT_SUCCESS);
}
