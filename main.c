#include "ArvoreAVL.h"


int main(int argc, char** argv) {
    if(argc != 3){
        printf("\tArgumento diferentes que 3\n");
        exit(-1);
    } else {
        printf("Argumento 1:%s\n",argv[0]);
        printf("Argumento 2:%s\n",argv[1]);
        printf("Argumento 3:%s\n",argv[2]);
    }

    Object Obj;
    char virg;
    int ret,ret2;
    PtrTreeAVL TreeAVL;
    iniciaArvoreAVL(&TreeAVL);
    FILE* arqEntrada = NULL;
    FILE* arqSaida = NULL;






    arqEntrada = fopen(argv[1], "r");
    if(arqEntrada == NULL){
        printf("Erro ao abrir arquivo Entrada.txt\n ");
        exit(1);
    } else {
        printf("Entrada.txt aberto com sucesso\n");
    }
    arqSaida = fopen(argv[2], "w");
    if(arqSaida == NULL){
        printf("Erro ao abrir arquivo Saida.txt\n ");
        exit(1);
    } else {
        printf("Saida.txt Aberto com sucesso\n");
    }



    fscanf(arqEntrada,"%i",&ret);
    fscanf(arqEntrada,"%c",&virg);
    Obj.key = ret;
    insertItem(&TreeAVL, Obj);
    while(virg == ','){
        ret2 = ret;
        fscanf(arqEntrada,"%i%c",&ret,&virg);
        Obj.key = ret;
        insertItem(&TreeAVL, Obj);
        if(ret2 == ret){
            printf("\n\tErro no formato de arquivo de entrada\n"
                   "Possiveis Erros:\n"
                   "\t1-Virgula após o último número de inserção\n"
                   "\t2-Números inseridos iguais apos o outro\n");
            exit(1);
        }
    }

    while(fscanf(arqEntrada,"%i%c",&ret,&virg) != EOF){
        removeAVL(&TreeAVL, ret);
    }







    printf("PreOrdem: ");
    preOrder(&TreeAVL);
    printf("\n");

    printf("PosOrdem: ");
    posOrder(&TreeAVL);
    printf("\n");

    printf("inOrdem Decresc: ");
    inOrderDecresc(&TreeAVL);
    printf("\n");


    //atualizarAltura(&TreeAVL);
    //imprimeArvoreAVLNivel(&TreeAVL);


    //printArvore(&TreeAVL);
//    PrintLevel(&TreeAVL);
//    int key = 9;
//    removeAVL(&TreeAVL, key);
//    key = 8;
//    removeAVL(&TreeAVL, key);


    printf("inOrdem Decresc: ");
    inOrderCresc(&TreeAVL);
    printf("\n");

    PrintLevel(&TreeAVL);

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
