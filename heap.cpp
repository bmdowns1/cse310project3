#include "heap.h"
#include <climits>
#include <iostream>

bool isEmpty;

HEAP* initializeHeap(int n)
{
	HEAP* heap = new HEAP();
	heap->numVertexes = n;
	vertexes* ptrs = new vertexes[heap->numVertexes];
	for (int i = 0; i < heap->numVertexes; i++)
	{
		ptrs[i] = new vertex();
	}
	heap->v = ptrs;
	heap->size = 0;
	heap->capacity = heap->numVertexes;
	return heap;
}
vertex* extractMin(HEAP* heap, int flag)
{
	heap->v[0]->pos = 0;
	vertex* vert = heap->v[0];
	heap->v[0] = heap->v[heap->size - 1];
	heap->size--;
	heap->v[0]->pos = 1;
	if (heap->size == 0)
	{
		isEmpty = true;
	}

	if (flag == 1) {
		printf("Delete vertex% d, key = % 12.4f\n", vert->id, vert->distance);
	}
	heapify(heap, heap->size, 0);
	return vert;
}
void upwardHeapify(HEAP* heap, int index)
{
	for (int i = index; heap->v[i]->distance < heap->v[parent(i)]->distance && i != 0; i = parent(i))
	{
		//swap vertexes
		vertex* vert = heap->v[i];
		heap->v[i] = heap->v[parent(i)];
		heap->v[parent(i)] = vert;
		//swap positions
		int tmp  = heap->v[i]->pos;
		heap->v[i]->pos = heap->v[parent(i)]->pos;
		heap->v[parent(i)]->pos = tmp;
	}
}
void heapify(HEAP *heap, int size, int index) 
{
	int left = ((2 * index) + 1);
	int right = ((2 * index) + 2);
	int least = index;
	if (left < heap->size){
		if (heap->v[left]->distance < heap->v[least]->distance) {
			least = left;
		}
	}
	if (right < heap->size) {
		if (heap->v[right]->distance < heap->v[least]->distance) {
			least = right;
		}
	}
	if (least != index)
	{
		vertex tmp = *heap->v[index];
		heap->v[index] = heap->v[least];
		*heap->v[least] = tmp;

		int tmpPos = heap->v[index]->pos;
		heap->v[index]->pos = heap->v[least]->pos;
		heap->v[least]->pos = tmpPos;

		heapify(heap, size, least);
	}
}
int parent(int i)
{
	return ((i - 1) / 2);
}
bool isInHeap(HEAP* heap, vertex vert)
{
	for (int i = 0; i < heap->size; i++)
	{
		if (heap->v[0]->id == vert.id)
		{
			return true;
		}
	}
	return false;
}
void insertHeap(HEAP* heap, vertex* v, int flag)
{
		isEmpty = false;
		v->pos = heap->size + 1;
		heap->v[heap->size] = v;
		if (flag == 1)
		{
			printf("Insert vertex % d, key = % 12.4f\n", v->id, heap->v[heap->size]->distance);
		}
		heap->size++;
		upwardHeapify(heap, heap->size-1);
	
}
void decreaseKey(HEAP* queue, vertex* v, double distance, int flag)
{
	if (flag == 1)
	{
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v->id, v->distance, distance);
	}
	queue->v[v->pos-1]->distance = distance;
	upwardHeapify(queue, v->pos-1);
}



bool isHeapEmpty()
{
	return isEmpty;
}