# project1
Shared Memory

## Project Objectives:
The purpose of this project is to introduce students to the concept of shared memory and the problems that can occur if shared memory is not protected adequately. 

### Total points Available:
100

### Due:
October13at11:59 pm

## Project Description:
In this project, you need tocreate 4processes. Each of these processes will share a variable named "total". Within each process, you needto create a loop and increasethe variable “total” one by one until 100,000, 200,000, 300,000 and 500,000 respectively. Print out the value of “total” after each process finishes the loop.Make sure that onlythe newlycreated child calls the function “process#()”  After all the children have finished, the parent process should release the shared memory and terminate. Use the "wait"function so that the parent knows exactlywhen eachchildcompletes. The parent should print the process id of each child as the child finishes execution. Then it should release shared memory and print "End of Program".You need to run the program several times and write a reportto describe your observationsand analyze your results. 

## Sample output:
From Process 1: Counter= 100001
From Process 2: Counter = 200054
From Process 3: Counter = 300085
From Process 4: Counter = 500000
Child with ID 9099 has just exited.
Child with ID 9100 has just exited.
Child with ID 9098 has just exited.
Child with ID 9101 has just exited.
End of program.
