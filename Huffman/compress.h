#ifndef COMPRESS_H
#define COMPRESS_H
#include "building.h"
void frequency_count(FILE* arquivo, int* array);
BYTE add_bit(BYTE c_saida, short int pos);
void compress();
void write_compress(BYTE tabela[][150], FILE* arquivo, FILE* saida, int tree_size);
void creat_table(BYTE tabela[][150], Tree* bt, BYTE *string, int position);
#endif // COMPRESS_H