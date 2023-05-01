#include "queue.h"

typedef struct tree {
    int frequency;
    struct tree *next;
} Tree;

typedef struct priority_queue {
    Tree *head;
} priority_queue;

// Remove o nó com a menor frequência da fila.
Tree* dequeue(priority_queue *pq){
    if(pq->head == NULL)
        return NULL;
    Tree *aux = pq->head;
    pq->head = pq->head->next;
    aux->next = NULL;
    return aux;
}

// Cria uma fila de prioridade vazia.
priority_queue* create_priority_queue(){
    priority_queue *new_pq = malloc(sizeof(priority_queue));
    new_pq->head = NULL;
    return new_pq;
}

// Adiciona um novo nó à fila com base em sua frequência.
void enqueue(Tree *new_node, priority_queue *pq){
    if(pq->head == NULL || pq->head->frequency >= new_node->frequency){
        new_node->next = pq->head;
        pq->head = new_node;
        return ;
    }
    Tree *aux = pq->head;
    while(aux->next != NULL && aux->next->frequency < new_node->frequency)
        aux = aux->next;
    new_node->next = aux->next;
    aux->next = new_node;
    return ;
}
