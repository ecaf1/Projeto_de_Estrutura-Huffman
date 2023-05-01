#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "building.h"

// Função que escreve a descompressão do arquivo
void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo);

// Verifica se o arquivo possui extensão .huff
int verification(char *nome);

// Função principal de descompressão
void decompress();

#endif // DECOMPRESS_H
