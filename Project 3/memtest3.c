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
    int i;
	int size;
	srand(time(NULL));

	printf("***** Allocating 2^16 - 1 entries of random sizes  *****\n");
	for (i = 0; i < 0xFFFF; i++) {
	    size = sizeof(char) * ((rand() % 20) + 1);
	    malloc(size);
	}
	
	exit(0);
}
