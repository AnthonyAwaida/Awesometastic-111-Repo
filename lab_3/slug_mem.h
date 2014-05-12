// CREATED

#include <unistd.h>
#include <time.h>

#define malloc(s) slug_malloc((s))
#define FUNCTIONIZE(a,b) a(b)
#define STRINGIZE(a) #a
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i)
#define FILE_POS __FILE__ ":" INT2STRING(__LINE__)

#define MAX_ALLOC_SIZE 128
#define FALSE 0
#define TRUE 1

typedef struct *node Node;

typedef struct Node {
    int block_size;
	void *address;
	char *caller;
	time_t time_stamp;
	Node next;
	Node prev;
} Node;

typedef struct Mem {
    Node first;
	Node last;
	Node current;
	int mem_size;
} Mem;

void *slug_malloc (size_t size, char *WHERE);
void slug_free ( void *addr, char *WHERE );
void slug_memstats ( void );
