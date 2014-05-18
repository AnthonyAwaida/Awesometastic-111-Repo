// CREATED

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX_ALLOC_SIZE (size_t) pow(2.0, 27.0)
#define FALSE 0
#define TRUE 1

typedef struct _Node Node;
typedef struct _Mem Mem;

void *slug_malloc (size_t size, char *WHERE);
void slug_free ( void *addr, char *WHERE );
void slug_memstats ( void );