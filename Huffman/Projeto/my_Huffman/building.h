#include "tree.h"
#include "queue.h"

Tree *func_exception(FILE *file);
Tree *rebuild_huffman_tree (FILE *FILE);
Tree *build_tree(priority_queue *pq);
Tree *build_huffman_tree(int *array);
int creating_huffman_string(Tree *huffman, FILE *file);