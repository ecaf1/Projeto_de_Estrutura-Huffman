#include "tree.h"

// Cria um novo nó com o caractere e a frequência especificados
Tree* create_node(BYTE character, int frequency) {
    Tree* new_node = (Tree*) malloc(sizeof(Tree)); // Aloca espaço de memória para o novo nó
    new_node->character = character;
    new_node->frequency = frequency;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Escreve a árvore no cabeçalho do arquivo
void write_tree(Tree* root, int* size, FILE* header) {
    // Verifica se o nó atual é uma folha
    if(root->left == NULL && root->right == NULL){
        // Verifica se o caractere é '\' ou '*'
        if(root->character == '\\' || root->character == '*'){
            // Escreve o caractere '\' antes do caractere especial
            BYTE aux = '\\';
            (*size)++;
            fprintf(header, "%c", aux);
        }
        (*size)++;
        fprintf(header, "%c", root->character);
        return;
    }
    // Escreve o caractere do nó atual
    (*size)++;
    fprintf(header, "%c", root->character);
    // Percorre a subárvore esquerda, se existir
    if(root->left != NULL)
        write_tree(root->left, size, header);
    // Percorre a subárvore direita, se existir
    if(root->right != NULL)
        write_tree(root->right, size, header);
}
