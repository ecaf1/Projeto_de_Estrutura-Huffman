#include "building.h"

// Função que lê um caractere do arquivo e cria um nó da árvore de Huffman com ele,
// retornando esse nó. A função é usada para criar exceções na árvore, quando um caractere
// especial precisa ser representado na árvore.
Tree *func_exception(FILE *arquivo)
{
    BYTE character;
    fscanf(arquivo, "%c", &character);

    Tree *h_tree = creat_node(character,0);
    fscanf(arquivo, "%c", &character);
    if(character == '\\') fscanf(arquivo, "%c", &character);
    h_tree->left = creat_node(character, 0);
    return (Tree*) h_tree;

}
// Função que reconstrói a árvore de Huffman a partir de um arquivo. Ela lê o caractere atual
// do arquivo, e se for diferente de "*", cria um novo nó com o caractere lido e retorna ele.
// Caso contrário, ela cria um nó com "*" e chama recursivamente a função para criar as subárvores
// à esquerda e à direita desse nó. Quando a função chega ao final do arquivo, ela retorna a raiz
// da árvore de Huffman.
Tree* rebuild_huffman_tree (FILE *arquivo)
{

    int condition = 1;
    BYTE character;

    fscanf(arquivo, "%c", &character);

    if(character != '*')
    {
        condition = 0;
    }
    if(character == '\\')
    {
        fscanf(arquivo, "%c", &character);
        condition = 0;
    }
    Tree *h_tree = creat_node(character,0);
    if(condition)
    {
        h_tree->left = rebuild_huffman_tree(arquivo);
        h_tree->right = rebuild_huffman_tree(arquivo);
    }

	return (Tree*)h_tree;
}
// Função que constrói a árvore de Huffman a partir da fila de prioridade de nós. Ela retira os dois
// nós de menor frequência da fila, cria um novo nó pai com "*" e esses dois nós como filhos, e adiciona
// esse novo nó na fila. O processo se repete até que reste apenas um nó na fila, que será a raiz da árvore
// de Huffman. A função retorna esse nó raiz.
Tree* build_huffman_tree(int *array)
{
    
    priority_queue *pq = creat_priority_queue();
    Tree *huffman_tree;

    int i;

    for(i = 255; i >= 0; i--){
        if(*(array+i) != 0)
            enqueue(creat_node(i, *(array+i)), pq);
    }

    huffman_tree = build_Tree(pq);

    return  (Tree*)huffman_tree;
}
// Função que constrói a árvore de Huffman a partir da fila de prioridade de nós. Ela retira os dois
// nós de menor frequência da fila, cria um novo nó pai com "*" e esses dois nós como filhos, e adiciona
// esse novo nó na fila. O processo se repete até que reste apenas um nó na fila, que será a raiz da árvore
// de Huffman. A função retorna esse nó raiz.
Tree* build_Tree(priority_queue *pq)
{

    Tree *aux;

    while(1){

        aux = creat_node('*', 0);
        aux->left = dequeue(pq);
        
        if(aux->left != NULL)
            aux->frequency += aux->left->frequency;
        
        aux->right = dequeue(pq);
        if(aux->right != NULL)
            aux->frequency += aux->right->frequency;
        
        if(pq->head == NULL)
            break;
        
        enqueue(aux, pq);
        
    }
    return aux;
}
// Função que escreve a árvore de Huffman em um arquivo de cabeçalho. Ela usa uma representação
// pré-ordem para a árvore, escrevendo um caractere "*" para cada nó interno e um caractere especial "\""
// antes de cada caractere especial (nós folha). A função também atualiza o tamanho da string escrita.
// Ela retorna o tamanho da string escrita.
int creating_huffman_string(Tree *huffman, FILE *header)
{
  
    int *size = (int*) malloc(sizeof(int));
    BYTE aux = 0;
    (*size) = 0;
    fprintf(header, "%c", aux);
    fprintf(header, "%c", aux);
    write_Tree(huffman, size, header);

    return (*size);
}


















/*

O código é composto por diversas funções que juntas constroem a árvore de Huffman a partir de um arquivo de entrada,
 e depois geram um arquivo de saída codificado usando a árvore de Huffman.

A primeira função, func_exception, é responsável por tratar exceções quando se constrói a árvore de Huffman.
 Ela lê um caractere do arquivo de entrada e cria um nó com esse caractere, que será a raiz da subárvore.
  Em seguida, lê outro caractere e verifica se é o caractere de escape ''. 
  Se for, lê mais um caractere e o atribui como o filho esquerdo do nó criado anteriormente. 
  Caso contrário, esse segundo caractere será atribuído como filho esquerdo. A função retorna um ponteiro para a subárvore criada.

A segunda função, rebuild_huffman_tree, é responsável por reconstruir a árvore de Huffman a partir do arquivo de entrada.
Ela lê um caractere do arquivo e verifica se é o caractere ''. Se não for, significa que se trata de um caractere folha e a função retorna um nó com esse caractere.
Caso seja '', ela verifica se o próximo caractere é um caractere de escape '' e, se for, lê mais um caractere.
Em seguida, ela cria um nó com o primeiro caractere lido e chama recursivamente a função para criar os filhos esquerdo e direito desse nó. 
A função retorna um ponteiro para a árvore criada.

A terceira função, build_huffman_tree, é responsável por construir a árvore de Huffman a partir de um vetor de frequências de caracteres.
Ela cria uma fila de prioridade vazia e, para cada posição no vetor de frequências com valor diferente de zero, cria um nó com o caractere correspondente e sua frequência e adiciona esse nó à fila de prioridade.
Em seguida, chama a função build_Tree para construir a árvore de Huffman a partir da fila de prioridade.
A função retorna um ponteiro para a raiz da árvore criada.

A quarta função, build_Tree, é responsável por construir a árvore de Huffman a partir da fila de prioridade.
Ela cria um nó vazio e, em seguida, remove os dois primeiros nós da fila de prioridade e os atribui como filhos esquerdo e direito desse nó.
Em seguida, soma as frequências dos dois nós filhos e atribui essa soma como frequência do nó pai.
 Se a fila de prioridade estiver vazia, a função retorna o nó pai criado. Caso contrário, ela adiciona o nó pai à fila de prioridade e repete o processo.

A quinta função, creating_huffman_string, é responsável por criar a string que representa a árvore de Huffman no arquivo de saída.
Ela aloca um inteiro para armazenar o tamanho da string e inicia esse tamanho com zero.
Em seguida, escreve dois caracteres nulos no arquivo de saída, que serão substituídos posteriormente pelo tamanho da string e pela própria string. 
Em seguida, chama a função write_Tree para escrever a árvore de Huffman no arquivo de saída. A função retorna o tamanho da string criada.


*/