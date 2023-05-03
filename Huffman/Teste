#include "compress.h"
#include "decompress.h"

int main(){

    int option;

    // loop infinito até que o usuário selecione uma opção válida
    while(1){

        // exibe as opções de compressão e descompressão
        printf("Escolha uma das opcões: \n");
        printf("Digite 1 para comprimir. \n");
        printf("Digite 2 para descomprimir.\n");

        // lê a opção escolhida pelo usuário
        scanf("%d",&option);
        getchar();

        // executa a opção escolhida pelo usuário ou exibe uma mensagem de erro se a opção for inválida
        switch(option){
            case 1:
                compress();
                break;
            case 2:
                decompress();
                break;
            default:
                printf("Digite uma opção válida! Tente Novamente :) .\n");
                continue;
        }

        // pausa a execução do programa e limpa a tela
        system("pause");
        system("cls");

        // encerra o loop
        break;
    }

    getchar();

}
