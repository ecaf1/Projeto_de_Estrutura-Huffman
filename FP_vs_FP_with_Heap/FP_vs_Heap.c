#include "Heap.h"
#include "FP.h"
#include <time.h>
int main(){
    Node *heap = (Node*)malloc(sizeof(Node));
    heap->size = 0;
    // Seed para a função rand() gerar números aleatórios diferentes a cada execução
    srand(time(NULL));
    // Insere 500 números aleatórios na Heap
    for (int i = 0; i < 500; i++) {
        int num = rand() % 1000; // Gera um número aleatório entre 0 e 999
        enqueue(heap, num); // Insere o número na Heap
    }
    return 0;
}

