/**
 * Cyrus Baker
 * Kay Sweebe
 * CS 474 - T. Wang
 * Project 1 - Shared Memory
 *
 * Purpose:
 *
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* key number */
#define SHMKEY ((key_t) 1497) // we could make private later? IPC_PRIVATE

/* shared memory */
typedef struct
{
	int value;
} shared_mem;

shared_mem * total; 

int main()
{
	int shmid, pid1, pid2, pid3, pid4, ID, status;
	char *shmadd;
	shmadd = (char *) 0;

	/* Create and connect to a shared memory segment */
	if ( (shmid = shmget( SHMKEY, sizeof(int), IPC_CREAT | 0666) ) < 0 ){
		perror("shmget");
		exit(1);
	}// end if

	if ( (total = (shared_mem *) shmat(shmid, shmadd, 0)) == (shared_mem *) - 1 ){
		perror("shmat");
		exit(0);
	}// end if

	/* Initialize shared memory to 0 */	total->value = 0;

	/* Create processes */
	// Creating first child
	int n1 = fork();

	// Creating second child.
	// First child also executes this line to create grandchild
	int n2 = fork();

	if (n1 > 0 && n2 > 0) {
		printf("\n\nParent\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
		printf("my parentid is %d \n", getppid());
	}
	else if (n1 == 0 && n2 > 0)
	{
		printf("\n\nFirst child\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
		printf("my parentid is %d \n", getppid());
	}
	else if (n1 > 0 && n2 == 0)
	{
		printf("\n\nSecond child\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
		printf("my parentid is %d \n", getppid());
	}
	else
	{
		printf("\n\nThird child\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
		printf("my parentid is %d \n", getppid());
	}

	/* Parent waits for child process to finish and print ID of each child */
// NEEDS WORK STILL
	int i, stat; // check i
	pid_t pid[5];
	for (i = 0; i < 5; i++)
	{
		if ((pid[i] = fork()) == 0)
		{
			sleep(1);
			exit(100 + i);
		}
	}//end for

	// Using waitpid() and printing exit status
	// of children.
	for (i = 0; i < 5; i++ )
	{
		pid_t cpid = waitpid(pid[i], &stat, 0);
		if (WIFEXITED(stat))
			printf("Child %d terminated with status: %d\n",
					cpid, WEXITSTATUS(stat));
	}//end for

	for (i = 0; i < 5; i++)
	{
		if ((pid[i] = fork()) == 0)
		{
			sleep(1);
			exit(100 + i);
		}
	}//end for

	// Using waitpid() and printing exit status
	// of children.
	for (i = 0; i < 5; i++ )
	{
		pid_t cpid = waitpid(pid[i], &stat, 0);
		if (WIFEXITED(stat))
			printf("Child %d terminated with status: %d\n",
					cpid, WEXITSTATUS(stat));
	}//end for



	/* Detach shared memory, use shmdt(total); */

	/* Remove shared memory, use shmctl(shmid, IPC_RMID, NULL);
	 * After a shared memory is removed, it no longer exists
	 */

}// end main


void process1(){
	for ( int i = 0; i < 1000; i++ )
	    total = total + 1;
}

void process2(){
	for( int i = 0; i < 1000; i++ )
	    total = total + 1;
}
void process3(){
	for( int i = 0; i < 1000; i++ )
	    total = total+ 1;
}
void process4(){
	for( int i = 0; i < 2000; i++ )
	    total = total + 1;
}
