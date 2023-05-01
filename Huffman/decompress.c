#include "decompress.h"

// Esta função usa a árvore de Huffman para descomprimir o arquivo compactado
void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo){
// Inicializa a árvore auxiliar como a raiz da árvore de Huffman
Tree *aux = bt;
BYTE character, aux1;
int i;

Copy code
// Lê o primeiro byte do arquivo compactado
fscanf(entrada, "%c", &character);
aux1 = character;

// Percorre cada bit do arquivo compactado para descomprimir o texto
while(fscanf(entrada, "%c", &character) != EOF){

    // Percorre a árvore de Huffman para encontrar o caractere correspondente
    for(i = 7; i >= 0; i--){

        if(aux->left == NULL && aux->right == NULL){
            // Quando um caractere é encontrado, ele é escrito no arquivo de saída
            fprintf(saida,"%c",aux->character);
            // A árvore auxiliar é reinicializada como a raiz da árvore de Huffman
            aux = bt;
        }

        // Percorre para a esquerda se o bit for 0, e para a direita se for 1
        if(aux1 & 1<<i)
            aux = aux->right;
        else
            aux = aux->left;
    }
    aux1 = character;
}

// Se houver lixo, processa os bits restantes
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

// Verifica se o arquivo tem a extensão .huff, indicando que é um arquivo compactado
int verification(char *nome){
int condition = 0,i,j,size = strlen(nome);
char *huff;
huff = ".huff";

Copy code
// Verifica os últimos 5 caracteres do nome do arquivo
for(i = size-1,j = 4 ; i>size-6 ; i--,j--)
    if(huff[j] != nome[i])condition = 1;

// Se a extensão não for .huff, exibe uma mensagem de erro e retorna 1
if(condition){
    printf("Nao se trata de um arquivo compactado.\nArquivos compactados devem ter a extensao: .huff\n");
    system("pause");
}
return condition;
}

// Função principal para descomprimir o arquivo
void decompress(){
// Declaração das variáveis
char nome_entrada[100], nome_saida[100];
FILE *arquivo_entrada;
FILE *arquivo_saida;
BYTE character;
int lixo, size_tree = 0, i;
Tree *bt = NULL;

Copy code
// Loop para solicitar o nome do arquivo de entrada e saída
while(1){
    system("cls");
    printf("Digite o nome do arquivo:\n");
    scanf("%[^\n]s", nome_entrada);
    getchar();

    arquivo_entrada = fopen(nome_entrada, "rb");

    // Verifica se o arquivo de entrada existe
    if(arquivo_entrada == NULL){
        printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
        system("pause");
        continue;
    }
    // Verifica se o arquivo é um arquivo compactado
    if(verification(nome_entrada))continue;

    printf("O nome do arquivo de saida:\n");
    scanf("%[^\n]s", nome_saida);
    getchar();
    break;
}

system("cls");
printf("Aguarde ...\n");

// Lê o primeiro byte do arquivo compactado para obter o tamanho do lixo e da árvore de Huffman
fscanf(arquivo_entrada, "%c", &character);
lixo = character>>5;
size_tree = character & 0b00011111;
size_tree = size_tree << 8;
fscanf(arquivo_entrada, "%c", &character);
size_tree = size_tree | character;

system("cls");
printf("Aguarde ...\n");

// Reconstrói a árvore de Huffman a partir do arquivo compactado
if(size_tree == 2) bt = (Tree*)func_exception(arquivo_entrada);
else bt = rebuild_huffman_tree(arquivo_entrada);

arquivo_saida = fopen(nome_saida, "wb");

// Descomprime o arquivo e escreve o resultado no arquivo de saída
write_decompress(bt, arquivo_entrada, arquivo_saida, lixo);

printf(" Concluido com exito\n");

// Fecha os arquivos
fclose(arquivo_saida);
fclose(arquivo_entrada);

return;
}