/*  Demonstrates how fork() works
 *
 *  https://www.geeksforgeeks.org/fork-memory-shared-bw-processes-created-using/
 *
 *  So when we do  afork() what are the sections the two processes actually share?
 *  Is the heap memory per process?
 *  Are the global variables shared?
 *  Will malloc return the same address to both?
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int globalVar;

int main(void)
{
	int localVar = 0;
	int* p = (int*) malloc(2);
	pid_t childPID = fork();

	// Putting value at allocated address
	*p = 0;
	if (childPID >= 0) // fork successful
	{
		if (childPID == 0) // child process
		{
			printf("\nChild process initial value :: localVar"
				" = %d, globalVar = %d", localVar,
				globalVar);
			localVar++;
			globalVar++;

			int c = 500;
			printf("\nChild process :: localVar = %d, "
				"globalVar = %d", localVar, globalVar);
			printf("\nAddress of malloced mem child = %p "
				"and value is %d", p, *p);
			printf("\n let's change the value pointed my malloc");

			*p = 50;
			printf("\nAddress of malloced mem child = %p "
				"and value is %d", p, *p);

			printf("\n lets change the value pointed by "
				"malloc in child");

			*p = 200;
			printf("\nAddress of malloced mem child = %p "
				"and value is %d\n\n\n", p, *p);
		}// end child process
		else // Parent process
		{
			printf("\nParent process initial value :: "
				"localVar = %d, globalVar = %d",
				localVar, globalVar);

			localVar = 10;
			globalVar = 20;
			printf("\n Parent process :: localVar = %d, "
				"globalVar = %d", localVar, globalVar);
			printf("\nAddress of malloced mem parent = %p "
				"and value is %d", p, *p);
			            
			*p = 100;
            		printf("\n Address of malloced mem parent= %p "
                   		"and value is %d", p, *p);
            		printf("\n lets change the value pointed my"
                    		" malloc in child");
            
			*p = 400;
            		printf("\n Address of malloced mem child = %p"
                   		" and value is %d \n", p, *p);
		}// end parent process
	}// end if fork successful
	else // fork unsuccessful
	{
		printf("\nFork failed, quitting\n");
		return 1;
	}// end fork funsuccessful

	return 0;
}// end main
