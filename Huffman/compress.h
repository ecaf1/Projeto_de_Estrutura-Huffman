#ifndef COMPRESS_H
#define COMPRESS_H

#include "building.h"

// Frequência de contagem dos caracteres no arquivo original
void frequency_count(FILE arquivo, int* array);

// Adiciona um bit na posição especificada em um BYTE
BYTE addbit(BYTE csaida, short int pos);

// Cria a tabela com os caminhos de cada folha (caractere) na árvore de Huffman
void create_table(BYTE tabela[][150], Tree bt, BYTE *string, int position);

// Realiza a compressão dos dados
void compress();

// Escreve os bytes comprimidos no arquivo final
void writecompress(BYTE tabela[][150], FILE arquivo, FILE* saida, int treesize);

#endif // COMPRESS_H