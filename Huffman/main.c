#include "compress.h"
#include "decompress.h"

int main(){

    int option;

    while(1){

        printf("\tEscolha:\n");
        printf("\tDigite 1 para comprimir.\n");
        printf("\tDigite 2 para descomprimir.\n");
        printf("\t>> ");
        scanf("%d",&option);
        getchar();

        if(option == 1){
            compress();
            system("pause||echo");
            break;
        }
        else if(option == 2){
            decompress();
            system("pause||echo");
            break;
        }
        else{
            system("cls||clear");
            printf("Opcao invalida! Tente Novamente.\n");
        }
    }

    getchar();
}
