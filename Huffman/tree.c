#include "tree.h"

/*
A função creat_node é responsável por criar e retornar um novo nó da árvore Huffman. 
Recebe como argumentos um caractere e uma frequência inteira e aloca um novo nó dinamicamente, inicializando seus campos com os valores recebidos. 
Em seguida, retorna o ponteiro para o novo nó criado.
*/

Tree* creat_node(BYTE character, int frequencia){

    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->character= character;
    new_node->frequency = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
A função write_Tree é responsável por escrever a árvore Huffman em um arquivo de cabeçalho.
Recebe como argumentos um ponteiro para a raiz da árvore, um ponteiro para um inteiro que será utilizado para calcular o tamanho da árvore, e um ponteiro para o arquivo de cabeçalho. A função percorre a árvore em pré-ordem, escrevendo cada nó no arquivo de cabeçalho. Se o nó for uma folha, o caractere correspondente é escrito no arquivo. Se o caractere for uma barra invertida () ou asterisco (*), uma barra invertida é escrita antes do caractere para escapar a barra invertida ou asterisco.
Ao final, a função atualiza o tamanho da árvore através do ponteiro recebido.
*/

void write_Tree(Tree *root, int *size, FILE *header){

    if(root->left == NULL && root->right == NULL){

        if(root->character== '\\' || root->character== '*'){

            BYTE aux = '\\';
            (*size)++;
            fprintf(header, "%c", aux);
        }

        (*size)++;
        fprintf(header, "%c", root->character);

        return ;
    }
    (*size)++;
    fprintf(header, "%c", root->character);

    if(root->left != NULL)
        write_Tree(root->left, size, header);
    if(root->right != NULL)
        write_Tree(root->right, size, header);
}
