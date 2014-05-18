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

	int *invalid;
	/* regular allocation, no errors expected */
	int *test1 = (int *)malloc(sizeof(int));
	free(test1);
	free(test1);
	exit(0);
}
