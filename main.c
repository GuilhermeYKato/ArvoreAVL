#include "ArvoreAVL.h"


int main() {
    Object Obj;
    char virg;
    int ret;
    PtrTreeAVL TreeAVL;

    iniciaArvoreAVL(&TreeAVL);

    FILE* arqEntrada = NULL;
    FILE* arqSaida = NULL;

    arqEntrada = fopen("Entrada.txt", "r");
    if(arqEntrada == NULL){
        printf("Erro ao abrir arquivo Entrada.txt\n ");
        exit(1);
    } else {
        printf("Entrada.txt aberto com sucesso\n");
    }
    arqSaida = fopen("Saida.txt", "w");
    if(arqSaida == NULL){
        printf("Erro ao abrir arquivo Saida.txt\n ");
        exit(1);
    } else {
        printf("Saida.txt Aberto com sucesso\n");
    }

    while(fscanf(arqEntrada,"%i%c",&ret,&virg) != EOF){
        Obj.key = ret;
        insertItem(&TreeAVL, Obj);
        //printf("%i\n",ret);
        fprintf(arqSaida,"%i\n",ret);
    }
    preOrder(&TreeAVL);
    printf("\n");

    posOrder(&TreeAVL);
    printf("\n");

    inOrderDecresc(&TreeAVL);
    printf("\n");


    if(fclose(arqEntrada) != 0){
        printf("Erro ao fechar arquivo Entrada.txt\n");
        exit(1);
    } else {
        printf("Entrada.txt fechado com sucesso\n");
    }

    if(fclose(arqSaida) != 0){
        printf("Erro ao fechar arquivo saida.txt\n");
        exit(1);
    } else {
        printf("Saida.txt fechado com sucesso\n");
    }

    return 0;
}