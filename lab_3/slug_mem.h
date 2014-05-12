// CREATED

#include <unistd.h>

#define malloc(s) slug_malloc((s))
#define FUNCTIONIZE(a,b) a(b)
#define STRINGIZE(a) #a
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i)
#define FILE_POS __FILE__ ":" INT2STRING(__LINE__)

#define MAX_ALLOC_SIZE 128

typedef struct *node Node;

typedef struct node {
    int block_size;
	char alloc_state;
	Node next_node;
} node;

typedef struct mem {
    Node first;
	Node last;
	Node current;
	int mem_size;
} mem;

void *slug_malloc (size_t size, char *WHERE);
void slug_free ( void *addr, char *WHERE );
void slug_memstats ( void );
