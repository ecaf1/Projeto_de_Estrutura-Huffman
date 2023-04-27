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


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(Node *heap, int i){
    int largest;
    int left_index = i<<1;
    int right_index = (i<<1)+1;

    if (left_index <= heap->size && heap->priority_list[left_index] > heap->priority_list[i]){
        largest = left_index;
    }  
    else{
        largest = i;
    }  
    if (right_index <= heap->size && heap->priority_list[right_index] > heap->priority_list[largest]) {
        largest = right_index;
    }
    if (heap->priority_list[i] != heap->priority_list[largest]) {
        swap(&heap->priority_list[i], &heap->priority_list[largest]);
        max_heapify(heap, largest);
    }
}



void enqueue(Node *heap, int priority){
    if(heap->size >= MAX_SIZE) printf("Heap overflow");// caso a lista esteja cheia;
    else{
        heap->priority_list[++heap->size] = priority; // atualiza o size e adiciona mais um elemento no final da priority_list.
        int key_index = heap->size; //  Index do novo elemento
        int parent_index =  heap->size/2;  //  Index do pai do novo elemento.

        while (parent_index >= 1 && heap->priority_list[key_index] > heap->priority_list[parent_index]) {
            //  executa enquanto o pai do elemento adicionado não é a raiz da Heap e o novo elemento tem uma prioridade maior do que o pai 
            swap(&heap->priority_list[key_index], &heap->priority_list[parent_index]);//  Troca troca
            key_index = parent_index;  //tudo de novo
            parent_index = key_index/2;
        }
    }
}


/*
    Remove o elemento de maior prioridade (raiz da Heap) e mantém a propriedade de Heap
    Argumento:
        - heap: ponteiro para a raiz da Heap
    Retorno:
        - o elemento removido ou -1 se a Heap estiver vazia
*/
int dequeue(Node *heap) {
    // Verifica se a Heap está vazia
    if (heap == NULL) {
        printf("Heap underflow"); // Imprime uma mensagem de erro
        return -1; // Retorna um valor indicando que a Heap está vazia
    } else {
        // Remove o elemento de maior prioridade (raiz da Heap)
        int item = heap->priority_list[1];
        heap->priority_list[1] = heap->priority_list[heap->size]; // Substitui a raiz pelo último elemento adicionado
        heap->size--; // Atualiza o tamanho da Heap

        // Mantém a propriedade de Heap
        max_heapify(heap, 1);

        return item; // Retorna o elemento removido
    }
}


void heapsort(Node *heap){
    int i;
    for (i = heap->size; i >= 2; i--) {
        swap(&heap->priority_list[1], &heap->priority_list[i]);
        heap->size--;
        max_heapify(heap, 1);
    }
}

int main(){
    Node *heap = (Node*)malloc(sizeof(Node));
    heap->size = 0;
    enqueue(heap, 10);
    enqueue(heap, 13);
    enqueue(heap, 20);
    printf("%d", heap->priority_list[1]);
    return 0 ;
}