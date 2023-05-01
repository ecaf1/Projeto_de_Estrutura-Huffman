#ifndef QUEUE_H
#define  QUEUE_H

#include "tree.h"

// Estrutura da fila de prioridades
typedef struct priority_q {
    Tree *head; // Nó da árvore
} priority_queue;

// Cria e retorna uma fila de prioridades vazia
priority_queue* creat_priority_queue();

// Adiciona um nó à fila de prioridades com base em sua frequência
void enqueue(Tree *node, priority_queue *pq);

// Remove o nó da fila de prioridades com a menor frequência e o retorna
Tree* dequeue(priority_queue *pq);

#endif // QUEUE_H
