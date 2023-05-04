#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

/**

Métodos para Heaps:
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
    int priority_list[MAX_SIZE];// WARNING: priority_list[0] "não existe"
}Node;

//  *a = *b e *b = *a
void swap(int* a, int* b);

void max_heapify(Node *heap, int i);

void enqueue(Node *heap, int priority);

int dequeue(Node *heap);

void heapsort(Node *heap);

#endif