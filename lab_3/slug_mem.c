// CREATED

Mem memory;

void mem_init (void) {
        memory = malloc(MAX_ALLOC_SIZE);
	memory->first = NULL;
	memory->last = NULL;
	memory->current = NULL;
	memory->mem_size = MAX_ALLOC_SIZE;
	memory->num_alloca = 0;   //added this for counting total # of allocations done overall.
	memory->total_size = 0;
	memory->mean = 0;
	memory->SD = 0;
}

void insert_node (Node node) {
    if (memory->first == NULL) {
	    memory->first = memory->last = node;
	    memory->first->prev = memory->first->next = NULL;
	} else {
		node->prev = memory->last;
		memory->last->next = node;
	        memory->last = node;
	}
	memory->current = node;
	node->next = NULL;
	memory->num_alloca++;  //increase by 1 for each new allocation
	memory->total_size+=node->block_size;
	memory->mean = memory->total_size / memory->num_alloca;
}

int mem_is_valid (void *address, char *caller) {
    memory->current = memory->first;
	while (memory->current != NULL) {
	    if (memory->current->address == address && memory->current->caller == caller) {
		    return TRUE;
		}
		//doesn't the while loop needs to change the memory->current so it'll loop?  should add:
	          memory->current = memory->current->next;
	}
	return FALSE;
}

void *slug_malloc (size_t size, char *WHERE) {

    void *data_address;
	time_t allocation_time;
	
    /* Allocate a node */
    Node new_node = malloc(sizeof(Node));
	/* Handles errors */
	if (!new_node) {
	    fprintf (stderr, "ERR(%s): Cannot create node\n", strerror (errno));
	    return;
    }
	
	/* Allocate memory */
	data_address = malloc(size);
	/* Handles errors */
	if (!data_address) {
	    free(new_node);
	    fprintf (stderr, "ERR(%s): Cannot allocate %d in memory\n", strerror (errno), size);
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
	
        /* Insert node */
	insert_node(memory, new_node);  //did you called insert_node wrong?  it takes in a single node parameter 
	                                // shouldn't it be: insert_node(new_node); ?
}

void slug_free ( void *addr, char *WHERE ) {

    /* Check for memory validity, handles pointers, free memory and the node */
    if (mem_is_valid(addr, WHERE)) {
	    if (memory->current->prev != NULL) memory->current->prev->next = memory->current->next;
		if (memory->current->next != NULL) memory->current->next->prev = memory->current->prev;
		free(memory->current->address);
	    free(memory->current);
	}
}

void slug_memstats ( void ) {
	int Num_active_alloc=1;
	int total_active_size=0;
        
	Node node = malloc(sizeof(Node));
	node = memory->first;
	while(node !=NULL){

		printf("allocation[%d] %s(%11d) - size: %d, address: % p \n", 
		        Num_active_alloca, node->caller, node->time_stamp, node->block_size, node->address);
		Num_active_alloca++;
		total_active_size += node->block_size;
		node = node->next;
	}

	printf("----------------------------------------------------------\n");
	printf("*****               Allocation Summary               *****\n");
	printf("Total number of allocations done: %d\n", memory->num_alloca);
	printf("Total number of active allocation: %d\n", Num_active_alloca);
	printf("Total memory size of active allocation: %d\n", total_active_size);
	printf("Mean: %f   SD: %f\n",memory->mean, memory->SD);
	printf("----------------------------------------------------------\n");
}
