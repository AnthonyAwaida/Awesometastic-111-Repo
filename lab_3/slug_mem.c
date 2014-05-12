// CREATED

Mem memory;

void mem_init (void) {
    memory = malloc(MAX_ALLOC_SIZE);
	memory->first = NULL;
	memory->last = NULL;
	memory->current = NULL;
	memory->mem_size = MAX_ALLOC_SIZE;
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
}

int mem_is_valid (void *address, char *caller) {
    memory->current = memory->first;
	while (memory->current != NULL) {
	    if (memory->current->address == address && memory->current->caller == caller) {
		    return TRUE;
		}
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
	insert_node(memory, new_node);
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

}
