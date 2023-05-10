#include "queue.h"

/*
A função creat_priority_queue cria uma nova fila de prioridade, representada pela estrutura priority_queue.
 Ela aloca espaço na memória para a nova fila, inicializa a cabeça da fila como NULL e retorna um ponteiro para a nova fila.
*/
priority_queue* creat_priority_queue(){

    priority_queue *new_pq = (priority_queue*) malloc(sizeof(priority_queue));
    new_pq->head = NULL;
    return new_pq;
}
/*
A função dequeue é responsável por remover e retornar o elemento de maior prioridade da fila de prioridade, representada pela estrutura priority_queue.
Ela verifica se a cabeça da fila está vazia, se sim, retorna NULL.
Caso contrário, salva o nó da cabeça em uma variável auxiliar, atualiza a cabeça da fila para o próximo nó e retorna o nó salvo.
*/

Tree* dequeue(priority_queue *pq){
    if(pq->head == NULL)    return NULL;
    Tree *aux = pq->head;
    pq->head = pq->head->next;    
    aux->next = NULL; // WARNING
    return aux;
}
/*
A função enqueue insere um novo nó na fila de prioridade, representada pela estrutura priority_queue.
Ela verifica se a fila está vazia ou se o nó a ser inserido tem frequência maior ou igual à cabeça da fila, caso sim, o novo nó se torna a nova cabeça da fila.
Caso contrário, ela percorre a fila até encontrar a posição correta para inserir o novo nó, ou seja,
até encontrar um nó cuja frequência é menor que a frequência do novo nó.
Quando a posição correta é encontrada, o novo nó é inserido na frente do nó encontrado.
*/

void enqueue(Tree *new_node, priority_queue *pq){
    if(pq->head == NULL || pq->head->frequency >= new_node->frequency){
        new_node->next = pq->head;
        pq->head = new_node;
        return ;
    }
    Tree *aux = pq->head;
    while(aux->next != NULL && aux->next->frequency < new_node->frequency){
        aux = aux->next;
    }
    new_node->next = aux->next;
    aux->next = new_node;
    return ;
}
