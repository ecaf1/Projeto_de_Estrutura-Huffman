#include "building.h"

// Função que lê um caractere do arquivo e cria um nó da árvore de Huffman com ele,
// retornando esse nó. A função é usada para criar exceções na árvore, quando um caractere
// especial precisa ser representado na árvore.

Tree* func_exception(FILE *file){
    BYTE character;
    fscanf(file, "%c", &character);  //  scanf no arquivo

    Tree *h_tree = creat_node(character,0);
    if(character == '\\')  fscanf(file, "%c", &character);
    h_tree->left = creat_node(character, 0);
    return (Tree*) h_tree;
}


Tree* rebuild_huffman_tree(FILE *file){
    int condition = 1;
    BYTE character;
    fscanf(file, "%c", &character);
    if(character != '*')    condition = 0;
    if(character == '\\'){
        fscanf(file, "%c", &character);
        condition = 0;
    }
    Tree *h_tree = creat_node(character, 0);
    if(condition){
        h_tree->left = rebuild_huffman_tree(file);
        h_tree->right = rebuild_huffman_tree(file);
    }
    return (Tree*)h_tree;
}


Tree* build_huffman_tree(int *array){
    priority_queue *pq = creat_priority_queue(); // Cria uma nova fila de prioridades vazia
    Tree *huffman_tree; // Cria um ponteiro para a árvore de Huffman que será construída
    int i;
    for(i = 255; i >= 0; i--){ // Loop que percorre todas as posições do array de frequências
        if(*(array+i) != 0)     enqueue(creat_node(i, *(array+i)), pq); // Cria um novo nó para o caractere com frequência não nula e adiciona-o na fila de prioridades
    }
    huffman_tree = build_Tree(pq); // Constrói a árvore de Huffman a partir da fila de prioridades
    return huffman_tree; // Retorna a árvore de Huffman construída
}

Tree* build_Tree(priority_queue *pq){
    Tree *aux;
    while(1){
        aux = creat_node('*', 0);
        aux->left = dequeue(pq);
        if(aux->left != NULL)    aux->frequency += aux->left->frequency;
        aux->right = dequeue(pq);
        if(aux->right != NULL)    aux->frequency += aux->right->frequency;
        if(pq->head == NULL)    break;
        enqueue(aux, pq);
    }
    return aux;
}

int creating_huffman_strung(Tree *huffman, FILE *file){
    int *size = (int*) malloc(sizeof(int));
    BYTE aux = 0;
    (*size) = 0;
    fprintf(file, "%c", aux);
    fprintf(file, "%c", aux);
    write_Tree(huffman, size, file);
    return (*size);

}