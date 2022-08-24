#include "heap.h"

#include <stdlib.h>

Heap* heap_initialize(int dataSize, char* dataName, int (*comp)(void*, void*), void (*print)(void*))
{
	// Allocate space for a heap.
	Heap* heap = malloc(sizeof(*heap));

	// If we couldn't allocate space, return NULL.
	if(heap == NULL)
		return NULL;

	// Initialize the heap's array list.
	heap->list = alist_initialize(10, dataSize, dataName);

	// If we couldn't initialize the list, return NULL.
	if(heap->list == NULL)
		return NULL;
	
	// Store the compare and print functions for later.
	heap->compare = comp;
	heap->print   = print;
	
	// Return a pointer to the created heap.
	return heap;
}

bool heap_insert(Heap* heap, void* element)
{
	// If the heap or element are null, we should return false.
	if(heap == NULL || element == NULL)
		return false;
		
	// Add the element to the end of the list.
	alist_add(heap->list, element);
	
	// Heapify upward through the list starting at the last element.
	return _heapify_up(heap, heap->list->size-1);
}

void* heap_remove(Heap* heap)
{
	// If the heap is null, we should return NULL.
	if(heap == NULL)
		return NULL;

	// Swap the root value with the last value.
	alist_swap(heap->list, 0, heap->list->size-1);
	
	// Remove the last value (which was the root value).
	void* result = alist_remove(heap->list, heap->list->size-1);

	// Heapify down through the list and then return the outcome.
	return ( _heapify(heap, 0) ? result : NULL );
}

void* heap_peek(Heap* heap)
{
	// If the heap is null, we return NULL.
	if(heap == NULL)
		return NULL;

	// Return the value at the root.
	return alist_get(heap->list, 0);
}

int heap_size(Heap* heap)
{
	// If the heap is null, we return -1.
	if(heap == NULL)
		return -1;
	
	// Return the size of the underlying list.
	return heap->list->size;
}

bool heap_contains(Heap* heap, void* element)
{
	// If the heap or the element is null, we return null.
	if(heap == NULL || element == NULL)
		return false;

	// If the element has an index, return true. Otherwise return false.
	return ( alist_index_of(heap->list, element) >= 0 ? true : false );
}

bool _heapify(Heap* heap, int index)
{
	// If the heap is null, we return false.
	if(heap == NULL)
		return false;

	// If the heap is empty, or has a single element, it is
	// heapified by default. Return true.
	if(heap->list->size <= 1)
		return true;

	// If the index is out of bounds, we return false.
	if(index < 0 || index >= heap->list->size)
		return false;

	// Calculate the child indexes.
	int left  = (2 * index) + 1;
	int right = 2 * (index + 1);
	int top   = index;

	// Get the value from the given index, which is
	// the root of this subtree.
	void* root = alist_get(heap->list, top);

	// Get the values from the child indexes (if they exist).
	void* leftData  = (left  < heap->list->size ? alist_get(heap->list, left)  : NULL);
	void* rightData = (right < heap->list->size ? alist_get(heap->list, right) : NULL);
	
	// If the left child should be at the root of this subtree, set the
	// left data to be the new root data and set the current top to left.
	if(leftData != NULL && heap->compare(root, leftData) < 0)
	{
		root = leftData;
		top  = left;
	}
	
	// If the right value is actually a better choice for the root, update the top.
	if(rightData != NULL && heap->compare(root, rightData) < 0)
	{
		top = right;
	}	

	// Did we move the root? If so, we need to recurse from the new root position.
	if(top != index)
	{	
		// Swap the original index with the new top value.
		alist_swap(heap->list, index, top);
		
		// Top was the node the root swapped with, so it
		// is pointing to the current root. Recurse there.
		return _heapify(heap, top);
	}

	// Return true upon success.
	return true;
}

bool _heapify_up(Heap* heap, int index)
{
	// If the heap is null, we return false.
	if(heap == NULL)
		return false;

	// If the heap is empty, or has a single element, it is
	// heapified by default. Return true.
	if(heap->list->size <= 1)
		return true;

	// If the index is out of bounds, we return false.
	if(index < 0 || index >= heap->list->size)
		return false;

	// Calculate the parent index.
	int parentIndex  = (index - 1) / 2;

	// Get the value from the given index, which is the child.
	void* child = alist_get(heap->list, index);

	// Get the value from the parent index (if it exists).
	void* parent = ( parentIndex >= 0 ? alist_get(heap->list, parentIndex) : NULL );

	// If the child should be the parent, swap their positions and heapify up again..
	if(parent != NULL && heap->compare(parent, child) < 0)
	{	
		// Swap the parent and child values in the underlying array list..
		alist_swap(heap->list, parentIndex, index);
		
		// We should now heapify the new parent to make sure the heap
		// requirement is satisfied.
		return _heapify_up(heap, parentIndex);
	}

	// Return true upon success.
	return true;
}


