#include "compress.h"

// função para contar a frequência de cada byte no arquivo
void frequency_count(FILE* arquivo, int* array){
    BYTE character;
    while((fscanf(arquivo,"%c",&character)) != EOF){
        ++array[character];
    }
    return;
}

// função para adicionar um bit na posição correta na saída
BYTE addbit(BYTE csaida, short int pos){
    return (c_saida | (1<<(7-pos)));
}

// função para escrever os bytes comprimidos no arquivo de saída
void writecompress(BYTE tabela[][150], FILE* arquivo, FILE* saida, int treesize){
    BYTE aux, character = 0, cond = 1;
    short int size = 0, position = 0;
    while((fscanf(arquivo,"%c",&aux)) != EOF){
        position = 0;
        while(tabela[aux][position] != '\0'){
            if(size == 8){
                fprintf(saida,"%c",character);
                size = 0;
                character = 0;
            }
            if(tabela[aux][position] & 1) character = add_bit(character,size);
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

// função para criar a tabela de códigos a partir da árvore de Huffman
void creat_table(BYTE tabela[][150], Tree* bt, BYTE *string, int position){
    if(bt->left == NULL && bt->right == NULL){
        string[position] = '\0';
        strncpy(tabela[bt->character],string,position+1);
        return;
    }
    if(bt->left != NULL){
        string[position] = '0';
        creat_table(tabela,bt->left, string, position+1);
    }
    if(bt->right != NULL){
        string[position] = '1';
        creat_table(tabela,bt->right, string, position+1);
    }
}

// função principal para comprimir o arquivo
void compress(){
    char nome_entrada[200], nome_saida[200], aux[150];
    int frequency[256] = {0};
    FILE* arquivo;
    FILE* novo_arquivo;

    // obter os nomes dos arquivos de entrada e saída do usuário
    while(1){
        system("cls");
        printf("Digite o nome do arquivo:\n");
        scanf("%[^\n]s", nome_entrada);
        getchar();
        arquivo = fopen(nome_entrada,"rb");
        if(arquivo == NULL){
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        printf("Digite o nome do arquivo de saida:\n");
        scanf("%[^\n]s", nome_saida);
        getchar();
        break;
    }

    strcat(nome_saida,".huff");

    // contar a frequência de cada byte no arquivo
    frequency_count(arquivo, frequency);
    fseek(arquivo,0,SEEK_SET);

    // construir a árvore de Huffman e criar a tabela de códigos
    Tree* bt = build_huffman_tree(frequency);
    BYTE tabela[256][150];
    creat_table(tabela,bt,aux,0);

    novo_arquivo = fopen(nome_saida,"wb");

    // escrever o cabeçalho com o tamanho da árvore de Huffman
    int size_tree;
    BYTE aux1;
    size_tree = creating_huffman_string(bt, novo_arquivo);

    // escrever os bytes comprimidos no arquivo de saída
    write_compress(tabela,arquivo,novo_arquivo, size_tree);

    printf("Concluido com exito!");

    fclose(arquivo);
    fclose(novo_arquivo);
}