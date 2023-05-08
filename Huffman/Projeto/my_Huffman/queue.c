#include "queue.h"

// Função para remover o nó com menor frequência da fila de prioridade
Tree* dequeue(priority_queue *pq){
    // Verifica se a fila está vazia
    if(pq->head == NULL)    
        return NULL;

    // Armazena o nó com menor frequência e atualiza a cabeça da fila
    Tree *aux = pq->head;
    pq->head = pq->head->next;
    aux->next = NULL;
    return aux;
}

// Função para criar uma nova fila de prioridade
priority_queue* creat_priority_queue(){
    priority_queue *new_pq = (priority_queue*) malloc(sizeof(priority_queue));
    new_pq->head = NULL;
    return new_pq;
}

// Função para inserir um novo nó na fila de prioridade
void enqueue(Tree *new_node, priority_queue *pq){
    // Caso a fila esteja vazia ou a frequência do novo nó seja menor ou igual a do nó da cabeça da fila
    if(pq->head == NULL || pq->head->frequency >= new_node->frequency){
        new_node->next = pq->head;
        pq->head = new_node;
        return;
    }

    // Percorre a fila até encontrar o ponto de inserção do novo nó
    Tree *aux = pq->head;
    while(aux->next != NULL && aux->next->frequency < new_node->frequency){
        aux = aux->next;
    }
    new_node->next = aux->next;
    aux->next = new_node;
    return;
}
