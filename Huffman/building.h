#include "tree.h"
#include "queue.h"

// Função que cria a árvore de Huffman a partir do cabeçalho do arquivo
Tree rebuild_huffman_tree(FILE *arquivo);

// Função que constrói a árvore de Huffman a partir de um array de frequência
Tree build_huffman_tree(int *array);

// Função que constrói a árvore de Huffman a partir de uma fila de prioridade
Tree *build_tree(priority_queue *pq);

// Função que gera uma string de pré-ordem a partir da árvore de Huffman,
// escreve dois bytes vazios no início do arquivo de saída, e retorna o tamanho da árvore
int create_huffman_string(Tree *huffman, FILE *header);