#include <stdlib.h> 
#include <stdio.h> 
#include "slug_util.h"
#include <time.h>

/* Testing for
*invalid address
*already freed memory
*valid region
*/


int main(void){
    int *invalid;
	int size;
	srand(time(NULL));

	/* trying to deallocate an invalid address*/
	printf("***** Test for invalid address  *****\n");
	size = sizeof(char) * (rand() % (20));
	printf("Allocating %d Bytes\n", size);
	int *test1 = (int *)malloc(size);
	free(test1);
	free(invalid);
	
	/*trying to deallocate an already freed region*/
	printf("***** Test for already freed region  *****\n");
	size = sizeof(char) * (rand() % (20));
	printf("Allocating %d Bytes\n", size);
	int *test2 = (int *)malloc(size);
	free(test2);
	free(test2);
	
	/*trying to deallocate a valid region by passing in a pointer inside the region*/
	printf("***** Test for valid region  *****\n");
	size = sizeof(char) * (rand() % (20));
	printf("Allocating %d Bytes\n", size);
	int *test3 = (int *)malloc(size);
	size = sizeof(char) * (rand() % (20));
	printf("Allocating %d Bytes\n", size);
	int *test4 = (int *)malloc(size);
	
	printf("***** Not freeing either of them  *****\n");
	
	exit(0);
}
