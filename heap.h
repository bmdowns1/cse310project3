typedef struct vertex
{
	int id = -1;
	int color = 0; //0 white 1 grey 2 black
	double distance = 214748364;
	int predecessor = 0;
	int pos = -1;
}vertex;

typedef struct vertex* vertexes;
typedef struct heap
{
	vertexes* v;
	int numVertexes;
	int size;
	int capacity;
}HEAP;
HEAP* initializeHeap(int n);
vertex* extractMin(HEAP* heap, int flag);
bool isInHeap(HEAP* heap, vertex vert);
void insertHeap(HEAP* heap, vertex* v, int flag);
void upwardHeapify(HEAP* heap, int index);
void heapify(HEAP* heap, int size, int index);
int parent(int i);
bool isHeapEmpty();
void decreaseKey(HEAP* heap, vertex* v, double distance, int flag);