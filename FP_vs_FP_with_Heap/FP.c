#include <stdio.h>
#include <stdlib.h>

//  Criação classica de um No com 'int priority'     
typedef struct Node{
    int item;
    int priority;
    struct Node  *next;
}Node;

/* Isso daqui é para guardar a head da lista e para não fazer algo do tipo '**node', 
    vou usar somente porque acredito que simplifique um pouco a ideia.*/
typedef struct priority_queue {
Node *head;
}priority_queue;

//  Função poderosa que não pode faltar, não usei mudei de ideia.
int is_empty(Node *head){
return (head == NULL);
}


//  Adição de novo elemento checado a prioridade 
void enqueue(priority_queue *pq, int i, int p){
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->item = i;
    new_node->priority = p;
    //  Caso a lista NULL ou new_node possue a maior prioridade até então, new_node torna-se head.
    if ((pq == NULL) || (p > pq->head->priority)) {
        new_node->next = pq->head;
        pq->head = new_node;
    } 
    else {
        // Somente um pontero aux.
        Node *current = pq->head;
        // A cassada do No com priority <= p.
        while ((current->next != NULL) && (current->next->priority > p)) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Reita o elemento com maior prioridade, que seria o "último".
Node* dequeue(priority_queue *pq){
    if (pq == NULL) {
        printf("Priority Queue underflow");
        return NULL;   
    } 
    else {
        Node *node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL; // Isso daqui é por questão de seguraça! Caso contrario:
        return node;      //  O usuario teria acesso a lista toda.
    }
}

// Só retorna a maior pioridade da lista, caso exista.
int maximum(priority_queue *pq)
{
    if (pq == NULL) {
        printf("Priority Queue underflow");
        return -1;   
    } 
    else {
        return pq->head->item;
    }
}

int main(){
    return 0;
}