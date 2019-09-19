/* 
 * This is to demonstrate how many forks are necessary to create four processes.
 * Notice that only two forks are necessary.
 * Total number of processes = 2 ^n where n is the number of fork system calls.
 *
 * We start off with one process. When the first fork is called, one child is created
 * off of the one process. When the second fork is called, one child is created off 
 * process 1 and process 2.
 *
 *		process 1
 * 		|	\
 * 		| fork1  \ fork2
 * 		|	  \
 * 		process 2  process 3
 * 		|
 * 		| fork2
 * 		|
 * 		process 4
 *
 */	
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	fork();
	fork();

	printf("hello\n");
	return 0;
}// end main
