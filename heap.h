typedef struct vertex
{
	int id;
	int d = 999999999;
	int pi = 0;
}vertex;
typedef struct vertex* vertexes;
typedef struct heap
{
	vertexes* v;
	int numVertexes;
	int size;
	int capacity;
}HEAP;
void decreaseKey(HEAP* heap, int index, int val, int flag);
HEAP* initializeHeap(int n, int source);
bool isEmpty(HEAP* heap);
vertex* extractMin(HEAP* heap, int flag);
bool isInHeap(HEAP* heap, int index);
void insertHeap(HEAP* heap, vertex* v);
void upwardHeapify(HEAP* heap, int index);
void heapify(HEAP* heap, int size, int index);
int parent(int i);
