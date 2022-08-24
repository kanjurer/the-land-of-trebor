#include "queue.h"
#include <stdlib.h>

Queue* queue_initialize(int typeSize, char* typeName)
{
	// Create a linked list with its initialize function.
	LinkedList* list = llist_initialize(typeSize, typeName);

	// If the list couldn't be created, return NULL.
	if(list == NULL)
		return NULL;

	// Allocate enough memory for a queue.
	Queue* queue = malloc(sizeof(*queue));

	// If the queue couldn't be allocated, destroy
	// the list we made, then return NULL.
	if(queue == NULL)
	{
		llist_destroy(list);
		return NULL;
	}
	
	// If the list has been created, we can store it in the queue.
	queue->queue = list;

	// Return a pointer to the queue.
	return queue;	
}

bool queue_enqueue(Queue* queue, void* element)
{
	// If the queue is null, return false.
	// We don't need to check for the element being
	// NULL because the add_last function will do that.
	if(queue == NULL)
		return false;
	
	// Attempt to add the element to the end of
	// the list and return the result.
	return llist_add_last(queue->queue, element);
}

void* queue_dequeue(Queue* queue)
{
	// If the queue is null, we return false.
	if(queue == NULL)
		return NULL;
	
	// Remove the front of the list and return the value.
	return llist_remove_first(queue->queue);
}

void* queue_peek(Queue* queue)
{
	// Return the value at the front of the list.
	return llist_get(queue->queue, 0);
}

int queue_size(Queue* queue)
{
	// If the queue is null, we return -1.
	if(queue == NULL)
		return -1;
	
	// Return the size of the underlying list.
	return queue->queue->size;
}

bool queue_contains(Queue* queue, void* element)
{
	// If the queue is null, return NULL.
	if(queue == NULL)
		return NULL;
	
	// Find the index of the element in the linked list.
	int index = llist_index_of(queue->queue, element);
	
	// If the index is >= 0, then it must exist in the list,
	// so we return true. Otherwise we return false.
	return (index >= 0 ? true : false);
}

bool queue_destroy(Queue* queue)
{
	// If the queue is null, we return false.
	if(queue == NULL)
		return false;

	// Destroy the underlying linked list.
	llist_destroy(queue->queue);
	
	// Free the queue.
	free(queue);

	// Return successfully with true.
	return true;
}
