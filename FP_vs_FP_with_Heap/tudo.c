#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 50000

typedef struct Node_FP{
    int priority;
    struct Node_FP  *next;
}Node_FP;

typedef struct priority_queue {
Node_FP *head;
}priority_queue;

    typedef struct {
    int elastic_FP;
    int elstic_heap;
    int tam;
    int item;
} Dados;

int is_empty(Node_FP *head){
return (head == NULL);
}

priority_queue* create_priority_queue() {
    priority_queue* pq = (priority_queue*) malloc(sizeof(priority_queue));
    if (pq != NULL) {
        pq->head = NULL;
    }
    return pq;
}

void print_queue(priority_queue *queue){
    Node_FP *current = queue->head;
    while (current != NULL){
        printf("%d ", current->priority);
        current = current->next;
    }
}

int enqueue_FP(priority_queue *pq, int p){
    Node_FP *new_node = (Node_FP*) malloc(sizeof(Node_FP));
    new_node->priority = p;
    int count = 1;

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
            ++count;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    return count;
}

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

int maximum(priority_queue *pq){
    if (pq == NULL) {
        printf("Priority Queue underflow");
        return -1;   
    } 
    else {
        return pq->head->priority;
    }
}

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

int enqueue(Node *heap, int priority){
    int count = 1;// Variável contador para contar as interações
    if(heap->size >= MAX_SIZE){
        printf("Heap overflow");
        return -1;
    }// caso a lista esteja cheia;
    else{
        heap->priority_list[++heap->size] = priority; // atualiza o size e adiciona mais um elemento no final da priority_list.
        int key_index = heap->size; //  Index do novo elemento
        int parent_index =  heap->size/2;  //  Index do pai do novo elemento.

        while (parent_index >= 1 && heap->priority_list[key_index] > heap->priority_list[parent_index]) {
            //  executa enquanto o pai do elemento adicionado não é a raiz da Heap e o novo elemento tem uma prioridade maior do que o pai 
            swap(&heap->priority_list[key_index], &heap->priority_list[parent_index]);//  Troca troca
            key_index = parent_index;  //tudo de novo
            parent_index = key_index/2;
            count++;// Incrementa o contador de interações
        }
    }
    return count; // Retorna o número de interações realizadas
    
}

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

int main(){
    Node *heap = (Node*)malloc(sizeof(Node));
    heap->size = 0;

    priority_queue *queue = create_priority_queue();
    // Seed para a função rand() gerar números aleatórios diferentes a cada execução
    srand(time(NULL));

    Dados dados[500];
    FILE* arquivo = fopen("dados1.csv", "w");
    // Escreve o cabeçalho do CSV
    fprintf(arquivo, "elastic_FP,elastic_heap,tam,item\n");


    // Insere 500 números aleatórios na Heap
    for (int i = 0; i < 4900; i++) {
        int num = rand() % 100000 + 1; // Gera um número aleatório entre 0 e 999
        int elastic_2 = enqueue(heap, num); // Insere o número na Heap
        int elastic_1 = enqueue_FP(queue, num);
        fprintf(arquivo, "%d,%d,%d,%d\n", elastic_1, elastic_2, i, num);
    }
    fclose(arquivo);
    return 0;
}