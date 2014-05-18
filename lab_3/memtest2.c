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
	srand(time(NULL));
	int random = rand() % MAX_ALLOC_SIZE;
	int *invalid;

	/* trying to deallocate an invalid address*/
	printf("***** Test for invalid address  *****\n");
	int *test1 = (int *)malloc(sizeof(int)*random);
	free(test1, "memtest.c:21");
	free(invalid);
	
	/*trying to deallocate an already freed region*/
	printf("***** Test for already freed region  *****\n");
	int *test2 = (int *)malloc(sizeof(int)*random);
	free(test2, "memtest.c:28");
	free(test2, "memtest.c:28");
	
	/*trying to deallocate a valid region by passing in a pointer inside the region*/
	printf("***** Test for valid region  *****\n");
	int *test3 = (int *)malloc(sizeof(int)*random);
	int *test4 = (int *)malloc(sizeof(int)*random);
	free(test3, "memtest.c:35");
	free(test4, "memtest.c:36");
	
	return 0;
}
