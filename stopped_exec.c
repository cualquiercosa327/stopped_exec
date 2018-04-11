#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static char const msg_usage[] = "Usage: %s <command> [args]\nExecutes a program in stopped state.\n";

static
int usage(char const* cmd)
{
	fprintf(stderr, msg_usage, cmd);
	return 1;
}

int main(int argc, char *argv[])
{
	if( 2 > argc ){
		return usage(argv[0]);
	}
	pid_t const fork_rc = fork();
	if( 0 == fork_rc ){
		setsid();
		kill( 0, SIGSTOP );
		execvp(argv[1], argv+1);
		perror("execvp");
		return 2;
	}
	if( 0 > fork_rc ){
		perror("fork");
		return 3;
	}
	fprintf(stderr, "%ld\n", (long)fork_rc);
	return 0;
}
