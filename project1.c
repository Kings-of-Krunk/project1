#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h> //wait

/* key number */
#define SHMKEY ((key_t) 1497) // we could make private later? IPC_PRIVATE

/* shared memory */
typedef struct
{
	int value;
} shared_mem;

shared_mem * total; 

/* helper function declarations */
static void process1(void); 
static void process2(void); 
static void process3(void);
static void process4(void);

int main(void) {
  	int shmid, pid1, pid2, pid3, pid4, status;


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

   	/* Initialize total->value to 0 */
  	total->value = 0;

   	/* Create 4 processes and call increment functions for each*/
   	if (!(pid1 = fork()))
     		process1();
   	else if (!(pid2 = fork()))
      		process2();
   	else if (!(pid3 = fork()))
      		process3();
   	else if (!(pid4 = fork()))
	   	process4();
   	/* Poll for exit of processes */
   	else {
		/* first completion */
      		pid_t q1 = wait(&status);
      		if (WIFEXITED(status)){
      			printf("Completed = %d,", q1);
	        	printf(" Exit status = %d\n", WEXITSTATUS(status));
		}
	   	/* second completion */
      		pid_t q2 = wait(&status);
      		if (WIFEXITED(status)){
      			printf("Completed = %d,", q2);
	      		printf(" Exit status = %d\n", WEXITSTATUS(status));
		}
		/* third completion */
      		pid_t q3 = wait(&status);
      		if (WIFEXITED(status)){
      			printf("Completed = %d,", q3);
	      		printf(" Exit status = %d\n", WEXITSTATUS(status));
		}
	   	/* fourth completion */
      		pid_t q4 = wait(&status);
		if (WIFEXITED(status)){
			printf("Completed = %d,", q4);
	      		printf(" Exit status = %d\n", WEXITSTATUS(status));
		}
      		/* Memory */
      		if ((shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0)) == -1) {
         		perror("shmctl");
         		exit (-1);
      		}

      		/* EOP */
      		printf("\t\t  End of Program.\n");
   	}
   	return 0;
} 

static void process1(void) { 
   int k = 0;  
   while (k < 100000) {  
      k++;
      total->value = total->value + 1;  
    }  
    printf("From process 1 = %d\n", total->value); //<-- not quite right: could be >10000
}

static void process2(void) { 
   int k = 0;
   while (total->value != 100000)
      ;
   while (k < 100000) {  
      k++;
      total->value = total->value + 1;  
   }  
   printf("From process 2 = %d\n", total->value);
}

static void process3(void) { 
   int k = 0;  
   while (total->value != 200000)
      ;
   while (k < 100000) {  
      k++;
      total->value = total->value + 1;  
    }  
    printf("From process 3 = %d\n", total->value);
}

static void process4(void){
	int k = 0;
	while(total->value !=300000)
		;
	while ( k < 200000 ) {
		k++;
      		total->value = total->value + 1;
	}// end while
	printf("From process 4 = %d\n", total->value);
}// end process 4


