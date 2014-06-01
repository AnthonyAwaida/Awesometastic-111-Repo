#include <stdlib.h> 
#include <stdio.h> 
#include "slug_util.h"

/* needs to test the following functionality:
	* regular allocation & freeing
	* allocating size 0
	* allocating more than 128mb
	* memstats
*/
int main(void){

	/* regular allocation, no errors expected */
	int *test1 = (int *)malloc(sizeof(int));
	free(test1);
	free(test1);

	/* allocating zero space, expect message to stderr */
	size_t empty = (size_t) 0;
	char *test2 = (char *)malloc(empty);

   malloc(sizeof(char) * 16);
   malloc(sizeof(char) * 13);
   malloc(sizeof(char) * 11);

	/* allocating >= 128mb, should print to stderr and end */
	size_t too_much = MAX_ALLOC_SIZE;
	char *test3 = (char *)malloc(too_much);
	exit(0);
}
