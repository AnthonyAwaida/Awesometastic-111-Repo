// CREATED
#include "slug_mem.h"

struct _Node {
    int block_size;
	void *address;
	char *caller;
	time_t time_stamp;
	char freed;
	Node *next;
	Node *prev;
};

struct _Mem {
    Node *first;
	Node *last;
	Node *current;
	int act_alloca;
	int num_alloca;  //added this for counter total # of allocations done overall.
	int total_size;  //added for calculating the mean and SD of all allocation
	double mean;
	double SD;
};

Mem *memory;

void mem_init (void) {
    memory = malloc(MAX_ALLOC_SIZE);
	memory->first = NULL;
	memory->last = NULL;
	memory->current = NULL;
	memory->act_alloca = 0;
	memory->num_alloca = 0;   //added this for counting total # of allocations done overall.
	memory->total_size = 0;
	memory->mean = 0;
	memory->SD = 0;
}

void insert_node (Node *node) {
    if (memory->first == NULL) {
	    memory->first = memory->last = node;
	    memory->first->prev = memory->first->next = NULL;
	} else {
		node->prev = memory->last;
		memory->last->next = node;
	    memory->last = node;
	}
	node->next = NULL;
	node->freed = FALSE;
	memory->current = node;
	memory->num_alloca++;  //increase by 1 for each new allocation
	memory->total_size+=node->block_size;
	memory->mean = (double)memory->total_size / memory->num_alloca;
}

int mem_is_valid (void *address, char *caller) {
    memory->current = memory->first;
	while (memory->current != NULL) {
	    if (memory->current->address == address) {
	    	if(memory->current->freed == FALSE) return TRUE;
	    	else {
				printf("%s: Memory address %d is previously freed\n", caller, address);
			    return FALSE;
			}
		}
	    memory->current = memory->current->next;
	}
	printf("%s: Memory address %d is invalid\n", caller, address);
	return FALSE;
}

void *slug_malloc (size_t size, char *WHERE) {

    /* Init memory if it hasn't been done */
	if (memory == NULL) mem_init();
	
    void *data_address;
	time_t allocation_time;

	/* check that the allocation is of legal size */
	if (size >= MAX_ALLOC_SIZE){
		printf("%s: Cannot allocate more than 128MB \n", WHERE);
		slug_exit(1);
	} else if (size <= 0) {
	    printf("%s: Non-sense to allocate a memory of size %d\n", WHERE, size);
		return;
	}
	
    /* Allocate a node */
    Node *new_node = malloc(sizeof(Node));
	/* Handles errors */
	if (!new_node) {
	    printf("%s: Cannot create node\n", WHERE);
	    return;
    }
	
	/* Allocate memory */
	data_address = malloc(size);
	/* Handles errors */
	if (!data_address) {
	    free(new_node);
	    printf("%s: Cannot allocate %d in memory\n", WHERE);
	    return;
    }
	
	/* Saves address and size */
    new_node->address = data_address;
	new_node->block_size = size;
	
	/* Create time stamp */
	time(&allocation_time);
	new_node->time_stamp = allocation_time;
	
	/* Saves caller info */
	new_node->caller = WHERE;
	memory->act_alloca += 1;
	
    /* Insert node */
	insert_node(new_node);
	return data_address;
}

void slug_free ( void *addr, char *WHERE ) {
	if (memory == NULL) mem_init();
    /* Check for memory validity, handles pointers, free memory and the node */
    if (mem_is_valid(addr, WHERE)) {
	    free(memory->current->address);
	    memory->current->freed = TRUE;
		memory->act_alloca -= 1;
    }
}

void slug_memstats ( void ) {
	int active_alloc = 0;
	int total_active_size = 0;
	long long difference = 0;

	printf("----------------------------------------------------------\n");
	printf("*****               Active Allocations               *****\n");
	printf("----------------------------------------------------------\n");
	
	Node *node;
	node = memory->first;
	while(node != NULL){
		if(node->freed == FALSE){
			printf("allocation[%d] %s(%11d) - size: %d, address: %p \n", 
		        	active_alloc, node->caller, node->time_stamp, node->block_size, node->address);
			active_alloc++;
			total_active_size += node->block_size;
		}
		difference += (pow(node->block_size - memory->mean, 2.0));
		node = node->next;
	}
	memory->SD = sqrt((double)difference / memory->num_alloca);
	printf("----------------------------------------------------------\n");
	printf("*****               Allocation Summary               *****\n");
	printf("----------------------------------------------------------\n");
	printf("Total number of allocations done: %u\n", memory->num_alloca);
	printf("Total number of active allocation: %u\n", memory->act_alloca);
	printf("Total memory size of active allocations: %u\n", total_active_size);
	printf("Mean: %lf   SD: %lf\n", memory->mean, memory->SD);
}

void slug_exit(int exit_status) {
    if (memory != NULL)
		slug_memstats();
	printf("Exiting with status %d \n", exit_status);
	exit(exit_status);
}

