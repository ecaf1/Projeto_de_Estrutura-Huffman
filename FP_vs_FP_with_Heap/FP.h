#ifndef FP_H
#define FP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**

Métodos para PriorityQueue:
priority_queue* create_priority_queue();
void enqueue(priority_queue *pq, int i, int p);
node* dequeue(priority_queue *pq);
int maximum(priority_queue *pq);
int is_empty(priority_queue *pq);
*/
typedef struct Node_FP{
    int item;
    int priority;
    struct Node_FP  *next;
}Node_FP;

/* Isso daqui é para guardar a head da lista e para não fazer algo do tipo '**node', 
    vou usar somente porque acredito que simplifique um pouco a ideia.*/
typedef struct priority_queue {
Node_FP *head;
}priority_queue;

//  Função poderosa que não pode faltar, não usei mudei de ideia.
int is_empty(Node_FP *head);
//  Alocamento de memoria
priority_queue* create_priority_queue() ;
void print_queue(priority_queue *queue);
//  Adição de novo elemento checado a prioridade 
void enqueue_FP(priority_queue *pq, int i, int p);
// Reita o elemento com maior prioridade, que seria o "último".
Node_FP* dequeue_FP(priority_queue *pq);
// Só retorna a maior pioridade da lista, caso exista.
int maximum(priority_queue *pq);

#endif

