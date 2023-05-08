#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 256

typedef struct trienode {
    struct trienode *children[ALPHABET_SIZE];  // array de ponteiros para os filhos
    bool terminal;                             // indicador se o nodo é terminal (ou seja, se é o fim de uma palavra)
} trienode;

trienode* creatnode(){
    trienode *new_node = (trienode*)(malloc(sizeof(trienode)));  // aloca memória para um novo nodo
    for (int i = 0; i < ALPHABET_SIZE; i++)     new_node->children[i] = NULL;  // inicializa os filhos como NULL
    new_node->terminal = false;  // inicializa o indicador de terminal como falso
    return new_node;  // retorna o novo nodo
}

bool trieinsert(trienode **root, char *signedtext){
    if (*root == NULL)    *root = creatnode();  // se a raiz é NULL, cria um novo nodo

    unsigned char *text = (unsigned char*)signedtext;  // converte a string de entrada em um array de caracteres sem sinal
    trienode *aux = *root;  // cria um ponteiro auxiliar para percorrer a trie
    int lenght = strlen(signedtext);  // determina o comprimento da string de entrada

    for (int i = 0; i < lenght; i++){  // percorre a string de entrada caractere por caractere
        if (aux->children[text[i]] == NULL)    aux->children[text[i]] = createnode();  // se o filho para o caractere não existe, cria um novo nodo
        aux = aux->children[text[i]];  // move o ponteiro auxiliar para o nodo filho correspondente
    }
    if (aux->terminal)   return false;  // se o nodo atual já é terminal, a palavra já existe na trie
    else{
        aux->terminal = true;  // caso contrário, define o indicador de terminal para o nodo atual
        return true;  // retorna verdadeiro para indicar que a palavra foi inserida com sucesso
    }
}

void print_trie_rec(trienode *node, unsigned char *prefix, int lenght){   
    unsigned char newprefix[lenght+2];  // cria um novo array de caracteres sem sinal para armazenar o prefixo atualizado
    memcpy(newprefix,prefix,lenght);  // copia o prefixo existente para o novo array
    newprefix[lenght+1] = 0;  // adiciona o caractere nulo ao final do novo array

    if (node->terminal){  // se o nodo atual é terminal, imprime a palavra correspondente
        printf("WORD IS: %s\n", prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++){  // percorre todos os filhos do nodo atual
        if(node->children[i] != NULL){  // se o filho existe
            newprefix[lenght] = i;  // atualiza o prefixo adicionando o caractere correspondente
            print_trie_rec(node->children[i], newprefix, lenght+1);  // chama a função recursivamente com o filho atual e o novo prefixo
        }
    }
}


void print_trie(trienode * root){
    if(root == NULL){
        printf("TRIE EMPTY\n");
        return;
    }
    print_trie_rec(root, NULL, 0); // Chama a função que imprime a trie de forma recursiva
}

bool search_trie(trienode * root, char *signedtext){
    unsigned char *text = (unsigned char *) signedtext; // Converte o texto de entrada para unsigned char, que é utilizado na trie
    int lenght = strlen(signedtext); // Obtém o comprimento do texto
    trienode * tmp = root; // Cria um ponteiro temporário para a raiz da trie

    for (int i = 0; i < lenght; i++){ // Loop que percorre a trie para buscar o texto
        if (tmp->children[text[i]] == NULL)    return false; // Se não encontrar um filho para o caractere na posição i, retorna falso
        tmp = tmp->children[text[i]]; // Avança o ponteiro temporário para o próximo nó da trie
    }
    return tmp->terminal; // Retorna verdadeiro se o último nó encontrado é terminal
}

bool node_has_children(trienode * node){
    if (node == NULL) return false; // Se o nó for nulo, não tem filhos
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (node->children[i] != NULL)    return true; // Se encontrar um filho não nulo, tem filhos
    }
    return false; // Se chegou até aqui e não encontrou filhos, não tem filhos
}

trienode * delete_string_rec(trienode * node, unsigned char * text, bool * deleted){
    if(node == NULL) return node; // Se o nó for nulo, retorna nulo
    if (*text == '\0'){ // Se chegou ao final do texto
        if (node->terminal){ // Se o nó atual é terminal
            node->terminal = false; // Marca como não terminal
            *deleted = true; // Marca que a string foi deletada
            if (node_has_children(node) == false){ // Se o nó não tem filhos
                free(node); // Libera o espaço alocado para o nó
                node = NULL; // Marca como nulo
            }
        }
        return node; // Retorna o nó atual
    }
    node->children[text[0]] = delete_string_rec(node->children[text[0]], text+1, deleted); // Chama a função recursivamente para o próximo caractere

    if (*deleted && node_has_children(node) == false && node->terminal == false){ // Se a string foi deletada, o nó não tem filhos e não é terminal
        free(node); // Libera o espaço alocado para o nó
        node = NULL; // Marca como nulo
    }
    return node; // Retorna o nó atual
}

bool delete_string (trienode **root, char *signedtext){
    unsigned char *text = (unsigned char *) signedtext; // Converte o texto de entrada para unsigned char, que é utilizado na trie
    bool result = false;
    if (*root == NULL) return false; // Se a trie estiver vazia, retorna falso
    *root = delete_string_rec(*root, text, &result); // Chama a função recursiva para deletar a string
    return result; // Retorna verdade
}


int main(){
    trienode * root = NULL;

    trieinsert(&root, "GATO");
    trieinsert(&root, "SAPATO");
    trieinsert(&root, "RATO");
    trieinsert(&root, "CHATO");
    trieinsert(&root, "MATO");

    print_trie(root);
    printf("\n");

    printf("Buscando GATO: %d\n", search_trie(root, "GATO"));
    printf("Buscando SAPATO: %d\n", search_trie(root, "SAPATO"));
    printf("Buscando GATINHO: %d\n", search_trie(root, "GATINHO"));
    printf("\n");

    delete_string(&root, "CHATO");
    delete_string(&root, "MATO");

    print_trie(root);
}