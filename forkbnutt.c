#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>

int main(int argc, char *argv[]) 
{
	printf("ParentP-1st Message\n"); fflush(stdout);
	int rc = fork();
	if (rc < 0) 
	{ 	// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) 
	{ 	// CHILD code
		printf("Child 1-1stMessage\n"); fflush(stdout); 
		for(int i=0;i<INT_MAX/20;i++);//loops for 2147483648 times to slow down this example
		printf("Child 1-Final Message\n"); fflush(stdout); 
		exit(1);

	} else 
	{	// PARENT goes down this path (main)
		printf("ParentP-2nd Message\n"); fflush(stdout);
		wait(NULL);
		int rc=fork();
		if (rc<0)
		{ //fork failed
			fprintf(stderr,"Fork Failed\n");
			exit(1);
		} else if (rc == 0)
		{	//CHILD code
			printf("Child 2-MUST ONLY RUN WHEN CHILD 1 is DONE (no points if Child2 prints before child1 is done)\n"); fflush(stdout);
			printf("Child 2-Final Message\n"); fflush(stdout);
			exit(1);
		} else
		{	//PARENT
			printf("ParentP-3rd Message\n"); fflush(stdout);
		}
        wait(NULL);
		printf("ParentP-Final Message Must only run with Child1 and Child2 are done\n"); fflush(stdout);
	}
	for(int i=0;i<INT_MAX/2;i++);//loops for 2147483648 times to slow down this example
	return 0;
}
