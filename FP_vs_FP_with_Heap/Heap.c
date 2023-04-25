#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
/*
  Metodos para Heaps:
    heap* create_heap();
    void enqueue(heap *heap, int item);
    int dequeue(heap *heap);
    int get_parent_index(heap *heap, int i);
    int get_left_index(heap *heap, int i);
    int get_right_index(heap *heap, int i);
    void max_heapify(heap *heap, int i);
    int item_of(heap *heap, int i);
    void heapsort(heap *heap);
*/

typedef struct Node{
    int size;
    int priority_list[MAX_SIZE];
}Node;

void enqueue(Node *heap, int priority){
    if(heap->size >= MAX_SIZE) printf("Heap overflow");
    else{
        heap->priority_list[++heap->size] = priority;
        int key_index = heap->size;
        
    }
}

/*
Nao me aprece muito últeo e está errada as dunções, para concerta é so retornar heap->priority[j] e tratar overflow.

int get_parent_index(Node *heap, int i){
    return i/2;
}

int get_left_index(Node *heap, int i){
    return 2*i;
}

int get_right_index(Node *heap, int i){
    return 2*i +1;
}

*/
