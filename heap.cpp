#include "heap.h"
#include <climits>
HEAP* initializeHeap(int n, int source)
{
	HEAP* heap = new HEAP();
	heap->numVertexes = n;
	vertexes* ptrs = new vertexes[heap->numVertexes];
	for (int i = 0; i < heap->numVertexes; i++)
	{
		ptrs[i] = new vertex();
	}
	ptrs[0]->id = source;
	ptrs[0]->d = INT_MAX;
	ptrs[0]->pi = NULL;
	heap->v = ptrs;
	heap->size = 1;
	heap->capacity = heap->numVertexes;
	return heap;
}
void decreaseKey(HEAP* heap, int vertex, int val, int flag)
{																					
	heap->v[0]->d = val;													 
	upwardHeapify(heap, vertex);
}
vertex* extractMin(HEAP* heap, int flag)
{
	vertex* vert = heap->v[0];
	heap->v[0]->d = heap->v[heap->size - 1]->d;
	heap->size--;
	heapify(heap, heap->size, 0);
	return vert;
}
void upwardHeapify(HEAP* heap, int index)
{
	for (int i = index; heap->v[i]->d < heap->v[parent(i)]->d && i != 0; i = parent(i))
	{
		vertex* vert = heap->v[i];
		heap->v[i] = heap->v[parent(i)];
		heap->v[parent(i)] = vert;
	}
}
void heapify(HEAP *heap, int size, int index) 
{
	int left = ((2 * index) + 1);
	int right = ((2 * index) + 2);
	int least = index;
	if (left < heap->size){
		if (heap->v[left]->d < heap->v[least]->d) {
			least = left;
		}
	}
	if (right < heap->size) {
		if (heap->v[right]->d < heap->v[least]->d) {
			least = right;
		}
	}
	if (least != index)
	{
		vertex tmp = *heap->v[index];
		heap->v[index] = heap->v[least];
		*heap->v[least] = tmp;
		heapify(heap, size, least);
	}
}
int parent(int i)
{
	return ((i - 1) / 2);
}
bool isEmpty(HEAP* heap)
{
	if (heap->size == 0)
	{
		return true;
	}
	return false;
}
bool isInHeap(HEAP* heap, int index)
{
	for (int i = 0; i < heap->size; i++)
	{
		if (heap->v[0]->id == index)
		{
			return true;
		}
	}
	return false;
}
void insertHeap(HEAP* heap, vertex* v)
{
	if (heap->capacity >= heap->size)
	{
		heap->v[heap->size] = v;
		heap->size++;
	}
}