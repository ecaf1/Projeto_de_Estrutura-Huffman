#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char BYTE;  // Numero de 0 à255
typedef struct _tree Tree;  // Para possivelmente não usar ** e talvez ajudar na organização
typedef struct prioruty_q priority_queue;

struct _tree{
    int frequency;
    BYTE character;
    Tree *next;
    Tree *left;
    Tree *right;
};

Tree* creat_node(BYTE character, int frequencia);
void write_Tree(Tree *root, int *size, FILE *header);
#endif // TREE_H


