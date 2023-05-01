#include "building.h"

// Função para construir a árvore de Huffman a partir de um array de frequência de caracteres
// Retorna a raiz da árvore
Tree* build_huffman_tree(int *array){
    // Cria uma fila de prioridade vazia
    priority_queue *pq = creat_priority_queue();
    // Declara uma variável para armazenar a árvore de Huffman
    Tree *huffman_tree;

    int i;

    // Adiciona os nós folha à fila de prioridade
    for(i = 255; i >= 0; i--){
        if(*(array+i) != 0)
            enqueue(creat_node(i, *(array+i)), pq);
    }

    // Constrói a árvore de Huffman a partir da fila de prioridade
    huffman_tree = build_Tree(pq);

    return  (Tree*)huffman_tree;
}

// Função auxiliar para construir a árvore de Huffman a partir da fila de prioridade
// Retorna a raiz da árvore
Tree* build_Tree(priority_queue *pq){

    Tree *aux;

    while(1){

        // Cria um nó intermediário com "*" como caractere
        aux = creat_node('*', 0);
        // Adiciona o filho esquerdo
        aux->left = dequeue(pq);
        // Atualiza a frequência do nó intermediário
        if(aux->left != NULL)
            aux->frequency += aux->left->frequency;
        // Adiciona o filho direito
        aux->right = dequeue(pq);
        // Atualiza a frequência do nó intermediário
        if(aux->right != NULL)
            aux->frequency += aux->right->frequency;
        // Se a fila de prioridade estiver vazia, a árvore foi construída
        if(pq->head == NULL)
            break;
        // Adiciona o nó intermediário à fila de prioridade
        enqueue(aux, pq);
    }
    return aux;
}

// Função para escrever a árvore de Huffman no arquivo de cabeçalho
// Retorna o tamanho da string de Huffman
int creating_huffman_string(Tree *huffman, FILE *header){
    // Aloca espaço para armazenar o tamanho da string de Huffman
    int *size = (int*) malloc(sizeof(int));
    // Inicializa o tamanho como zero
    (*size) = 0;
    // Escreve dois bytes nulos para armazenar o tamanho posteriormente
    fprintf(header, "%c", 0);
    fprintf(header, "%c", 0);
    // Escreve a árvore de Huffman no arquivo e armazena o tamanho da string de Huffman
    write_Tree(huffman, size, header);

    return (*size);
}