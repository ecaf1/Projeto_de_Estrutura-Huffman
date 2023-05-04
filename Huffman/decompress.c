#include "decompress.h"

// A função é responsável por realizar a descompressão de um arquivo binário a partir da árvore de Huffman construída previamente.
// Recebe como parâmetros o ponteiro para a raiz da árvore de Huffman (Tree *bt), o ponteiro para o arquivo de entrada (FILE *entrada), o ponteiro para o arquivo de saída (FILE *saida) e o tamanho do lixo presente no arquivo de entrada (int lixo).
// A função percorre a árvore de Huffman de acordo com o bit lido no arquivo de entrada, até encontrar um nó folha que representa um caractere. Quando encontra, escreve o caractere correspondente no arquivo de saída.
// Essa operação é repetida para cada caractere do arquivo de entrada, até que se chegue ao fim do arquivo.
// Ao final do arquivo, caso haja bits restantes até completar um byte inteiro, esses bits são preenchidos com zeros e a operação de percorrer a árvore é realizada até encontrar o último nó folha.


void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo){
    Tree *aux = bt;
    BYTE character, aux1;
    int i;

    fscanf(entrada, "%c", &character);
    aux1 = character;

    while(fscanf(entrada, "%c", &character) != EOF){

        for(i = 7; i >= 0; i--){

            if(aux->left == NULL && aux->right == NULL){
                fprintf(saida,"%c",aux->character);
                aux = bt;
            }

            if(aux1 & 1<<i)
                aux = aux->right;
            else
                aux = aux->left;
        }
        aux1 = character;
    }

    for(i = 7; lixo <= 8; lixo++, i--){
        if(aux->left == NULL && aux->right == NULL)
        {
            fprintf(saida,"%c",aux->character);
            aux = bt;
        }
        if(aux1 & 1<<i)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return ;
}

// A função  é responsável por verificar se o arquivo passado como parâmetro é um arquivo de extensão .huff, indicando que se trata de um arquivo compactado. 
// Recebe como parâmetro o nome do arquivo (char *nome) e retorna 0 caso seja um arquivo válido ou 1 caso contrário.
// Caso o arquivo não seja válido, é exibida uma mensagem de erro indicando que o arquivo deve ter a extensão .huff.

int verification(char *nome){
    int condition = 0,i,j,size = strlen(nome);
    char *huff;
    huff = ".huff";

    for(i = size-1,j = 4 ; i>size-6 ; i--,j--)
        if(huff[j] != nome[i])condition = 1;

    if(condition){
        printf("Nao se trata de um arquivo compactado.\nArquivos compactados devem ter a extensao: .huff\n");
        system("pause||echo");
    }
    return condition;
}

// A função é responsável por iniciar o processo de descompressão de um arquivo binário a partir de sua representação em árvore de Huffman.
// A função não recebe parâmetros e não retorna nenhum valor. 
//O processo de descompressão é iniciado a partir da leitura do nome do arquivo de entrada e de saída pelo usuário.
// Após a verificação da extensão do arquivo de entrada, a função lê o tamanho do lixo presente no arquivo e o tamanho da árvore de Huffman.
// Em seguida, a árvore de Huffman é reconstruída a partir dos dados lidos do arquivo, e é realizada a descompressão do arquivo utilizando a função write_decompress.

void decompress(){

    char nome_entrada[100], nome_saida[100];

    FILE *arquivo_entrada;
    FILE *arquivo_saida;

    BYTE character;
    int lixo, size_tree = 0, i;
    Tree *bt = NULL;

    while(1){

        system("cls||clear");
        printf("Digite o nome do arquivo:\n");
        scanf("%[^\n]s", nome_entrada);
        getchar();

        arquivo_entrada = fopen(nome_entrada, "rb");

        if(arquivo_entrada == NULL){
            printf("O nome do arquivo ou caminho invalido!\n Tente novamente... :)");
            system("pause||echo");
            continue;
        }
        if(verification(nome_entrada))continue;
        printf("O nome do arquivo de saida:\n");
        scanf("%[^\n]s", nome_saida);
        getchar();
        break;
    }

    system("cls||clear");
    printf("Aguarde ...\n");

    // LÊ TAMANHO DO LIXO
    fscanf(arquivo_entrada, "%c", &character);
    lixo = character>>5;

    // LÊ O TAMANHO DA ARVORE
    size_tree = character & 0b00011111;
    size_tree = size_tree << 8;
    fscanf(arquivo_entrada, "%c", &character);
    size_tree = size_tree | character;

    system("cls||clear");
    printf("Aguarde ... :)\n");

    if(size_tree == 2) bt = (Tree*)func_exception(arquivo_entrada);
    else bt = rebuild_huffman_tree(arquivo_entrada);
    arquivo_saida = fopen(nome_saida, "wb");

    write_decompress(bt, arquivo_entrada, arquivo_saida, lixo);

    printf(" Concluido!\n");

    fclose(arquivo_saida);
    fclose(arquivo_entrada);

    return;
}

/*

O código em questão é um programa de descompressão de arquivos compactados no formato .huff. 
Ele é composto por diversas funções, cada uma com uma responsabilidade específica.
A função "verification" tem como objetivo verificar se o arquivo de entrada é realmente um arquivo compactado no formato .huff. 
Caso não seja, uma mensagem é exibida e o programa é encerrado.
A função "rebuild_huffman_tree" é responsável por reconstruir a árvore de Huffman a partir das informações contidas no arquivo compactado.
Ela utiliza as funções "create_node" e "insert_bt" para construir a árvore a partir das informações lidas do arquivo.
A função "create_node" é responsável por criar um novo nó da árvore de Huffman, inicializando seus valores com as informações lidas do arquivo compactado.
A função "insert_bt" é responsável por inserir um novo nó na árvore de Huffman, respeitando a ordem dos valores de frequência dos nós.
A função "func_exception" é responsável por tratar o caso em que o arquivo compactado não contém informações suficientes para a construção da árvore de Huffman.
Nesse caso, ela cria uma árvore com apenas um nó, cujo valor é o primeiro byte lido do arquivo compactado.
A função "write_decompress" é responsável por realizar a descompressão do arquivo compactado.
Ela utiliza a árvore de Huffman reconstruída para percorrer o arquivo compactado bit a bit, e escrever o valor de cada caractere na saída correspondente.
Por fim, a função "decompress" é a função principal do programa.
Ela é responsável por receber as informações de entrada do usuário, abrir os arquivos de entrada e saída, chamar as funções necessárias para a descompressão e 
fechar os arquivos ao final do processo.
Em resumo, o programa em questão é uma implementação do algoritmo de descompressão de arquivos compactados no formato .huff,
 utilizando uma estrutura de dados de árvore de Huffman para reconstruir os caracteres originais do arquivo descomprimido.

*/