#include "types.h"
#include "user.h"
#define WNOHANG 1

int exitWait(void)
{
	int pid;
	int ret_pid;
	int exit_status;
	int i;
	printf(1, "\n  Parts a and b) testing exit(int status) and "
		      "wait(int* status):\n");
	for (i = 0; i < 2; i++) 
	{
		pid = fork();
		if (pid == 0) // -> CHILD
		{
			if (i == 0)
			{
				printf(1, "\n This is child with PID# %d and I will exit with "
					      "status %d\n", getpid(), 0);
				exit(0);
			}
			else
			{
				printf(1, "\nThis is child with PID# %d and I will exit with "
					      "status %d\n", getpid(), -1);
				exit(-1);
			}
		}
		else if (pid > 0) // -> PARENT
		{ 
			ret_pid = wait(&exit_status);
			printf(1, "\n This is the parent: child with PID# %d has exited "
				      "with status %d\n", ret_pid, exit_status);
		}
		else  // -> fork() ERROR
		{
			printf(2, "\nError using fork\n");
			exit(-1);
		}
	}
	return 0;
}

int waitPid(void)
{
	int ret_pid;
	int exit_status;
	int i;
	int pid_a[5] = { 0, 0, 0, 0, 0 };
	printf(1, "\nPart c) testing waitpid(int pid, int* status, int options):\n");
	for (i = 0; i < 5; ++i) 
	{
		pid_a[i] = fork();
		if (pid_a[i] == 0)	// -> CHILD
		{
			printf(1, "\nThe is child with PID# %d and I will exit with "
				      "status %d\n", getpid(), getpid() + 4);
			exit(getpid() + 4);
		}
	}
	for (i = 4; i >= 0; --i)
	{
		sleep(5);
		printf(1, "\nThis is the parent: Now waiting for child with PID# "
			      "%d\n", pid_a[i]);
		ret_pid = waitpid(pid_a[i], &exit_status, 0);
		printf(1, "\nThis is the partent: Child# %d has exited with status %d"
			      "\n", ret_pid, exit_status);
	}
	return 0;
}

int CELEBW02(void)
{
	printf(1, "\n  Part e) the waitpid option WNOHANG, test program CELEBW02 \n");
	int pid;
	int retpid;
	int status;
	if ((pid = fork()) < 0)
	{
		printf(2, "fork() error");
	}
	else if (pid == 0)	// -> CHILD 
	{
		sleep(5);
		exit(1);
	}
	else
	{
		do
		{
			if ((retpid = waitpid(pid, &status, WNOHANG)) == -1)
			{
				printf(2, "wait() error");
			}
			else if (retpid == 0)
			{
				printf(1, "child is still running \n");
				sleep(1);
			}
			else
			{
				printf(1, "child exited with status of %d\n", status);
			}
		} while (retpid == 0);
	}
	return 0;
}

int main(int argc, char * argv[])
{
	printf(1, "\n This program tests the correctness of your lab#1\n");
	if (atoi(argv[1]) == 1)
	{
		exitWait();
	}
	else if (atoi(argv[1]) == 2)
	{
		waitPid();
	}
	else if (atoi(argv[1]) == 3)
	{
		CELEBW02();
	}
	else
	{
		printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to "
				  "test waitpid and \"lab1 3\" to test the extra credit "
			      "WNOHANG option \n");
	}
	exit(0);
	return 0;
}
