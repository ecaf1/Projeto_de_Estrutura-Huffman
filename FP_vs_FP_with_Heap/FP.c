#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**

Métodos para PriorityQueue:
priority_queue* create_priority_queue();
void enqueue(priority_queue *pq, int i, int p);
node* dequeue(priority_queue *pq);
int maximum(priority_queue *pq);
int is_empty(priority_queue *pq);
*/


//  Criação classica de um No com 'int priority'     
typedef struct Node_FP{
    int item;
    int priority;
    struct Node_FP  *next;
}Node_FP;

typedef struct priority_queue {
Node_FP *head;
}priority_queue;

void print_queue(priority_queue *pq){
    Node_FP *current = pq->head;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->priority);
        current = current->next;
    }
    printf("NULL\n");
}



/* Isso daqui é para guardar a head da lista e para não fazer algo do tipo '**node', 
    vou usar somente porque acredito que simplifique um pouco a ideia.*/


//  Função poderosa que não pode faltar, não usei mudei de ideia.
int is_empty(Node_FP *head){
return (head == NULL);
}

/*
  * Cria uma nova fila de prioridade e retorna um ponteiro para ela.
  * Aloca memória suficiente para a fila de prioridade usando a função malloc()
  * Inicializa o campo head com o valor NULL.
  * Retorna um ponteiro para a fila de prioridade recém-criada.
  */
priority_queue* create_priority_queue() {
    priority_queue* pq = (priority_queue*) malloc(sizeof(priority_queue));
    if (pq != NULL) {
        pq->head = NULL;
    }
    return pq;
}





//  Adição de novo elemento checado a prioridade 
void enqueue_FP(priority_queue *pq, int i, int p){
    Node_FP *new_node = (Node_FP*) malloc(sizeof(Node_FP));
    new_node->item = i;
    new_node->priority = p;


    //  Caso a lista NULL ou new_node possue a maior prioridade até então, new_node torna-se head.
    if ((pq == NULL) || (pq->head == NULL) || (p > pq->head->priority)) {// da B.O quando (pq->head == NULL), não da para acessar  (p > pq->head->priority)
        new_node->next = pq->head;
        pq->head = new_node;
    } 
    else {
        // Somente um pontero aux.
        Node_FP *current = pq->head;
        // A cassada do No com priority <= p.
        while ((current->next != NULL) && (current->next->priority > p)) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Reita o elemento com maior prioridade, que seria o "último".
Node_FP* dequeue_FP(priority_queue *pq){
    if (pq == NULL) {
        printf("Priority Queue underflow");
        return NULL;   
    } 
    else {
        Node_FP *node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL; // Isso daqui é por questão de seguraça! Caso contrario:
        return node;      //  O usuario teria acesso a lista toda.
    }
}

// Só retorna a maior pioridade da lista, caso exista.
int maximum(priority_queue *pq){
    if (pq == NULL) {
        printf("Priority Queue underflow");
        return -1;   
    } 
    else {
        return pq->head->item;
    }
}
/*
int main(){
    priority_queue *queue = create_priority_queue(); //  Creat priority queue
    srand(time(NULL)); // semente aleatoria 
    for (int i = 0; i < 500; i++) {
        int num = rand() % 1000; // Gera um número aleatório entre 0 e 999
        enqueue_FP(queue, 4);
    }
    print_queue(print_queue);
    return 0;
}
*/