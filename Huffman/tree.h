#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

// Define a estrutura para a árvore
typedef struct _tree {
    int freq;
    unsigned char character;
    struct _tree *next, *left, *right;
} Tree;

// Cria um novo nó para a árvore
Tree* create_node(unsigned char character, int freq);

// Escreve a árvore no cabeçalho do arquivo
void write_tree(Tree *root, int *size, FILE *header);

#endif // TREE_H