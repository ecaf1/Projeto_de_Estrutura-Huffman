#include "compress.h"

//Esta função lê um arquivo e cria um array de frequência para cada caractere.
//O array é passado como parâmetro e a função atualiza as frequências correspondentes de cada caractere.
void frequency_count(FILE* arquivo, int* array)
{

    BYTE character;

    while((fscanf(arquivo,"%c",&character)) != EOF)
    {
        ++array[character];
    }

    return;
}
//Esta função adiciona um bit ao BYTE de saída na posição especificada e retorna o BYTE resultante.
BYTE add_bit(BYTE c_saida, short int pos)
{
    return (c_saida | (1<<(7-pos)));
}
//Esta função comprime o arquivo lido e escreve a versão comprimida no arquivo de saída.
//Ela recebe como parâmetros uma tabela de codificação dos caracteres, o arquivo original, o arquivo de saída e o tamanho da árvore de Huffman.
//A função percorre o arquivo original, codifica cada caractere usando a tabela e escreve o resultado no arquivo de saída.
void write_compress(BYTE tabela[][150], FILE* arquivo, FILE* saida, int tree_size)
{

    BYTE aux,character= 0,cond = 1;
    short int size = 0,position = 0;

    while((fscanf(arquivo,"%c",&aux)) != EOF)
    {
        position = 0;

        while(tabela[aux][position] != '\0')
        {
            if(size == 8)
            {
                fprintf(saida,"%c",character);
                size = 0;
                character = 0;
            }
            if(tabela[aux][position] & 1)character = add_bit(character,size);
            ++size;
            ++position;
        }
    }

    BYTE lixo = (8 - size)<<5;
    fprintf(saida,"%c",character);

    //SETANDO O PRIMEIRO BYTE (BITS DO LIXO)

    fseek(saida,0,SEEK_SET);
    lixo = lixo | tree_size>>8;
    fprintf(saida, "%c", lixo);
    lixo = tree_size  & 255;
    fprintf(saida, "%c", lixo);

    return;
}

//Esta função cria uma tabela de codificação para cada caractere a partir da árvore de Huffman. A função percorre a árvore e gera um código binário para cada caractere.
// O código é armazenado em uma string que é adicionada à tabela.

void creat_table(BYTE tabela[][150], Tree* bt, BYTE *string, int position){

    if(bt->left == NULL && bt->right == NULL){
        string[position] = '\0';
        strncpy(tabela[bt->character],string,position+1);
        return;
    }
    if(bt->left != NULL)
    {
        string[position] = '0';
        creat_table(tabela,bt->left, string, position+1);
    }
    if(bt->right != NULL)
    {
        string[position] = '1';
        creat_table(tabela,bt->right, string, position+1);
    }
}

//Esta função é a função principal que chama todas as outras funções para comprimir um arquivo usando o algoritmo de Huffman. 
//A função solicita o nome do arquivo de entrada e o nome do arquivo de saída, lê o arquivo de entrada, cria a árvore de Huffman.
// E gera a tabela de codificação, escreve a árvore no arquivo de saída, comprime o arquivo de entrada e escreve a versão comprimida no arquivo de saída.

void compress()
{

    char nome_entrada[200],nome_saida[200],aux[150];
    int frequency[256] = {0};

    FILE* arquivo;
    FILE* novo_arquivo;

    while(1){

        system("cls||clear");
        printf("Digite o nome do arquivo: ");
        scanf("%[^\n]s", nome_entrada);
        getchar();
        arquivo = fopen(nome_entrada,"rb");
        if(arquivo == NULL){
            printf("O nome do arquivo ou caminho invalido!\n Tente novamente... :)");
            system("pause||echo");
            continue;
        }
        printf("Digite o nome do arquivo de saida:\n");
        scanf("%[^\n]s", nome_saida);
        getchar();
        break;
    }

    strcat(nome_saida,".huff");

    frequency_count(arquivo, frequency);
    fseek(arquivo,0,SEEK_SET);
    system("cls||clear");
    printf("Aguarde ... :)\n");

    Tree* bt = build_huffman_tree(frequency);
    system("cls||clear");
    printf("Aguarde ... :)\n");

    BYTE tabela[256][150];
    creat_table(tabela,bt,aux,0);

    system("cls||clear");
    printf("Aguarde ... :)\n");

    novo_arquivo = fopen(nome_saida,"wb");

    int size_tree;
    BYTE aux1;
    size_tree = creating_huffman_string(bt, novo_arquivo);

    write_compress(tabela,arquivo,novo_arquivo, size_tree);

    printf("Concluido!");

    fclose(arquivo);
    fclose(novo_arquivo);
}

/*O código em questão se trata de uma implementação de um algoritmo de compressão de arquivos de texto baseado em Huffman. 
O objetivo da compressão é reduzir o tamanho do arquivo original sem perda de informações, através da remoção de redundâncias presentes no texto.
O programa é dividido em cinco funções principais: frequency_count(), build_huffman_tree(), creating_huffman_string(), write_compress() e compress(). 

A função frequency_count() é responsável por contar a frequência de cada caractere presente no arquivo de entrada e armazenar essa informação em um array.
 Ela recebe como parâmetros o arquivo de entrada (que deve ser aberto em modo binário) e o array que armazenará a frequência dos caracteres.

A função build_huffman_tree() é responsável por construir a árvore de Huffman a partir do array de frequência gerado pela função frequency_count().
 Ela utiliza uma estrutura de dados do tipo Tree para representar cada nó da árvore. 
 Cada nó pode ser uma folha (representando um caractere) ou um nó interno (representando um conjunto de caracteres). Essa função retorna o ponteiro para o nó raiz da árvore.

A função creating_huffman_string() é responsável por percorrer a árvore de Huffman e gerar uma string que represente a árvore de forma compacta.
 Essa string é utilizada posteriormente na descompressão do arquivo.
  Ela recebe como parâmetros a raiz da árvore e o arquivo de saída (que deve ser aberto em modo binário). Essa função retorna o tamanho em bytes da string gerada.

A função write_compress() é responsável por percorrer o arquivo de entrada e escrever no arquivo de saída a versão comprimida do arquivo utilizando a árvore de Huffman e a string gerada pela função creating_huffman_string(). 
Ela recebe como parâmetros a tabela de códigos de Huffman (gerada pela função creat_table()),
o arquivo de entrada (que deve ser aberto em modo binário), o arquivo de saída (que deve ser aberto em modo binário) e o tamanho da string da árvore gerada pela função creating_huffman_string().

A função compress() é a função principal que coordena todas as outras funções.
 Ela solicita ao usuário o nome do arquivo de entrada e o nome do arquivo de saída, chama as funções frequency_count() e build_huffman_tree() para gerar a árvore de Huffman e a tabela de códigos de Huffman, respectivamente,
  e em seguida chama a função creating_huffman_string() para gerar a string da árvore.
Por fim, ela chama a função write_compress() para escrever a versão comprimida do arquivo no arquivo de saída.*/