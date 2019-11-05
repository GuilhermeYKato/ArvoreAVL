#ifndef ARVORESAVL_ARVOREAVL_H
#define ARVORESAVL_ARVOREAVL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int key;
} Object;

typedef struct NodeAVL *PtrTreeAVL;

typedef struct NodeAVL {
    Object element;
    PtrTreeAVL left;
    PtrTreeAVL right;
    PtrTreeAVL father; //OPCIONAL
    int bF;
} NodeAVL;

void iniciaArvoreAVL(PtrTreeAVL *node){
    (*node) = NULL;
    printf("Arvore AVL foi iniciada\n");
}
void rotacaoSimplesEsquerda(PtrTreeAVL *node){
    PtrTreeAVL p,u;
    p = (*node);
    u = p->right;
    p->right = u->left;
    u->left = p;
    p->bF = 0;
    (*node)=u;
}
void rotacaoSimplesDireita(PtrTreeAVL *node){
    PtrTreeAVL p,u;
    p = (*node);
    u = p->left;
    p->left = u->right;
    u->right = p;
    p->bF = 0;
    (*node)=u;
}
void rotacaoDuplaEsquerda(PtrTreeAVL *node){
    PtrTreeAVL p,v,u;
    p = (*node);
    u = p->right;
    v = u->left;
    p->right = v->left;
    u->left = v->right;
    v->right = u;
    v->left = p;
    //fator balancea;
    (*node) = v;
}
void rotacaoDuplaDireita(PtrTreeAVL *node){
    PtrTreeAVL p,v,u;
    p = (*node);
    u = p->left;
    v = u->right;
    u->right = v->left;
    p->left = v->right;
    v->left = u;
    v->right = p;
    //fator balancea;
    (*node) = v;
}
int alturaArvoreAVL(PtrTreeAVL *lado){//PtrTreeAVL direito ou esquerdo
    if((*lado) == NULL){
        return 0;
    } else {
        int he = alturaArvoreAVL(&(*lado)->left);
        int hd = alturaArvoreAVL(&(*lado)->right);
        if (he < hd){
            return hd + 1;
        } else {
            return he + 1;
        }
    }
}
int atualizaBfArvoreAVL(PtrTreeAVL esquerda, PtrTreeAVL direita){
    int ae,ad;
    ae = alturaArvoreAVL(&esquerda);
    ad = alturaArvoreAVL(&direita);
    if(ae > ad){
        return ae;// ae +1
    } else {
        return ad;// ae +1
    }
}
void aplicarRotacoes(PtrTreeAVL *node){
    int ae,ad;
    PtrTreeAVL u;
    if(alturaArvoreAVL(&(*node)->left) > alturaArvoreAVL(&(*node)->right)){ //bF -2 (sendo negativa rotações p/ direita)
        u = (*node)->left;
        ae = alturaArvoreAVL(&u->left);
        ad = alturaArvoreAVL(&u->right);
        if(ad > ae){//quando a arvore direita é maior
            printf("\tRotação Dupla Direita\n");
            rotacaoDuplaDireita(&(*node));
        } else {//quando a arvore esquerda é maior
            printf("\tRotação Simples Direita\n");
            rotacaoSimplesDireita(&(*node));
        }
        
    } else { //bF +2 (sendo positiva rotações p/ esquerda)
        u = (*node)->right;
        ae = alturaArvoreAVL(&u->left);
        ad = alturaArvoreAVL(&u->right);
        if((ae > ad)){//quando a arvore esquerda é maior
            printf("\tRotação Dupla Esquerda\n");
            rotacaoDuplaEsquerda(&(*node));
        } else {//quando a arvore direita é maior
            printf("\tRotação Simples Esquerda\n");
            rotacaoSimplesEsquerda(&(*node));
        }
    }

}

bool insertItem(PtrTreeAVL *node, Object x){
    if((*node) == NULL){
        (*node) = malloc(sizeof(NodeAVL));
        (*node)->right = (*node)->left = NULL;
        (*node)->element = x;
        (*node)->bF = 1;
        printf("Elemento inserido: %d\n",(*node)->element.key);
        return true;
    }
    if((*node)->element.key == x.key){
        return false;
    }
    bool aux;
    if((*node)->element.key > x.key){
        aux = (insertItem(&(*node)->left,x));
    } else {
        aux = (insertItem(&(*node)->right, x));
    }
    if(!aux) return false;
    int ae, ad;
    ae = alturaArvoreAVL(&(*node)->left);
    ad = alturaArvoreAVL(&(*node)->right);

    if((ad - ae == -2) || (ad - ae == +2)){
        printf("\tBaguio ta desbalanceado\n");
        aplicarRotacoes(&(*node));
    }
    (*node)->bF = atualizaBfArvoreAVL((*node)->left, (*node)->right);
    return true;
}


bool estaVaziaArvoreAVL(PtrTreeAVL *node);

void preOrder(PtrTreeAVL *node){
//    printf("P");
    if((*node) != NULL){
        printf("%d ", (*node)->element.key);
        preOrder(&(*node)->left);
        preOrder(&(*node)->right);
    }
}

void posOrder(PtrTreeAVL *node){
    if((*node) != NULL){
        posOrder(&(*node)->left);
        posOrder(&(*node)->right);
        printf("%d ", (*node)->element.key);
    }
}

void inOrderCresc(PtrTreeAVL *node){
    if((*node) != NULL){
        inOrderCresc(&(*node)->left);
        printf("%d ", (*node)->element.key);
        inOrderCresc(&(*node)->right);
    }

}

void inOrderDecresc(PtrTreeAVL *node){
    if((*node) != NULL){
        inOrderDecresc(&(*node)->right);
        printf("%d ", (*node)->element.key);
        inOrderDecresc(&(*node)->left);
    }
}


bool pesquisaArvoreAVL(PtrTreeAVL *node);
void destruirArvoreAVL(PtrTreeAVL *node);

PtrTreeAVL getMinAux (PtrTreeAVL *node){//usado na remoção
    PtrTreeAVL Aux;
    if((*node)->left == NULL){
        Aux = (*node);
        (*node)=(*node)->right;
        return Aux;
    } else {
        return getMinAux(&(*node)->left);
    }
//    Aux = (*node);
//    while(Aux->left != NULL){
//        Aux = Aux->left;
//    }
//    (*node) = (*node)->right;
//    return (*node);
}
PtrTreeAVL getMaxAux (PtrTreeAVL *node) { //usado na remoção

    PtrTreeAVL Aux;
    if((*node)->right == NULL) {
        Aux = (*node);
        (*node) = (*node)->left;
        return Aux;
    } else {
        return getMaxAux(&((*node)->right));
    }
    //    Aux = (*node);
//    while(Aux->right != NULL){
//        Aux = Aux->right;
//    }
//    (*node) = (*node)->left;
//    return Aux;
}

bool removeAVL(PtrTreeAVL *node,int key){
    bool test;
    int he, hd;
    if((*node) == NULL){
        return false;
    }
    PtrTreeAVL Aux = NULL;
    if((*node)->element.key == key){
        if((*node)->left == NULL && (*node)->right != NULL){
            (*node) = (*node)->right;

        } else if((*node)->left != NULL && (*node)->right == NULL){//arvore direita NULA
            (*node) = (*node)->left;

        } else if((*node)->left == NULL && (*node)->right == NULL){//arvore esqueda NULA
            (*node) = NULL;

        } else if((*node)->left != NULL && (*node)->right != NULL){//((*node)->left != NULL && (*node)->right != NULL)
            Aux = getMinAux(&((*node)->right));
//            Aux = getMaxAux(&((*node)->left));
            (*node)->element = Aux->element;
            printf("Elemento Removido com Sucesso: %d\n",key);
        }
        free(Aux);

        return true;
    }

}

void imprimeArvoreAVLNivel(PtrTreeAVL *node){

}

#endif //ARVORESAVL_ARVOREAVL_H
#ifndef ARVORESAVL_ARVOREAVL_H
#define ARVORESAVL_ARVOREAVL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int key;
} Object;

typedef struct NodeAVL *PtrTreeAVL;

typedef struct NodeAVL {
    Object element;
    PtrTreeAVL left;
    PtrTreeAVL right;
    PtrTreeAVL father; //OPCIONAL
    int bF;
} NodeAVL;

void iniciaArvoreAVL(PtrTreeAVL *node){
    (*node) = NULL;
    printf("Arvore AVL foi iniciada\n");
}
void rotacaoSimplesEsquerda(PtrTreeAVL *node){
    PtrTreeAVL p,u;
    p = (*node);
    u = p->right;
    p->right = u->left;
    u->left = p;
    p->bF = 0;
    (*node)=u;
}
void rotacaoSimplesDireita(PtrTreeAVL *node){
    PtrTreeAVL p,u;
    p = (*node);
    u = p->left;
    p->left = u->right;
    u->right = p;
    p->bF = 0;
    (*node)=u;
}
void rotacaoDuplaEsquerda(PtrTreeAVL *node){
    PtrTreeAVL p,v,u;
    p = (*node);
    u = p->right;
    v = u->left;
    p->right = v->left;
    u->left = v->right;
    v->right = u;
    v->left = p;
    //fator balancea;
    (*node) = v;
}
void rotacaoDuplaDireita(PtrTreeAVL *node){
    PtrTreeAVL p,v,u;
    p = (*node);
    u = p->left;
    v = u->right;
    u->right = v->left;
    p->left = v->right;
    v->left = u;
    v->right = p;
    //fator balancea;
    (*node) = v;
}
int alturaArvoreAVL(PtrTreeAVL *lado){//PtrTreeAVL direito ou esquerdo
    if((*lado) == NULL){
        return 0;
    } else {
        int he = alturaArvoreAVL(&(*lado)->left);
        int hd = alturaArvoreAVL(&(*lado)->right);
        if (he < hd){
            return hd + 1;
        } else {
            return he + 1;
        }
    }
}
int atualizaBfArvoreAVL(PtrTreeAVL esquerda, PtrTreeAVL direita){
    int ae,ad;
    ae = alturaArvoreAVL(&esquerda);
    ad = alturaArvoreAVL(&direita);
    if(ae > ad){
        return ae;// ae +1
    } else {
        return ad;// ae +1
    }
}
void aplicarRotacoes(PtrTreeAVL *node){
    int ae,ad;
    PtrTreeAVL u;
    if(alturaArvoreAVL(&(*node)->left) > alturaArvoreAVL(&(*node)->right)){ //bF -2 (sendo negativa rotações p/ direita)
        u = (*node)->left;
        ae = alturaArvoreAVL(&u->left);
        ad = alturaArvoreAVL(&u->right);
        if(ad > ae){//quando a arvore direita é maior
            printf("\tRotação Dupla Direita\n");
            rotacaoDuplaDireita(&(*node));
        } else {//quando a arvore esquerda é maior
            printf("\tRotação Simples Direita\n");
            rotacaoSimplesDireita(&(*node));
        }
        
    } else { //bF +2 (sendo positiva rotações p/ esquerda)
        u = (*node)->right;
        ae = alturaArvoreAVL(&u->left);
        ad = alturaArvoreAVL(&u->right);
        if((ae > ad)){//quando a arvore esquerda é maior
            printf("\tRotação Dupla Esquerda\n");
            rotacaoDuplaEsquerda(&(*node));
        } else {//quando a arvore direita é maior
            printf("\tRotação Simples Esquerda\n");
            rotacaoSimplesEsquerda(&(*node));
        }
    }

}

bool insertItem(PtrTreeAVL *node, Object x){
    if((*node) == NULL){
        (*node) = malloc(sizeof(NodeAVL));
        (*node)->right = (*node)->left = NULL;
        (*node)->element = x;
        (*node)->bF = 1;
        printf("Elemento inserido: %d\n",(*node)->element.key);
        return true;
    }
    if((*node)->element.key == x.key){
        return false;
    }
    bool aux;
    if((*node)->element.key > x.key){
        aux = (insertItem(&(*node)->left,x));
    } else {
        aux = (insertItem(&(*node)->right, x));
    }
    if(!aux) return false;
    int ae, ad;
    ae = alturaArvoreAVL(&(*node)->left);
    ad = alturaArvoreAVL(&(*node)->right);

    if((ad - ae == -2) || (ad - ae == +2)){
        printf("\tBaguio ta desbalanceado\n");
        aplicarRotacoes(&(*node));
    }
    (*node)->bF = atualizaBfArvoreAVL((*node)->left, (*node)->right);
    return true;
}


bool estaVaziaArvoreAVL(PtrTreeAVL *node);

void preOrder(PtrTreeAVL *node){
//    printf("P");
    if((*node) != NULL){
        printf("%d ", (*node)->element.key);
        preOrder(&(*node)->left);
        preOrder(&(*node)->right);
    }
}

void posOrder(PtrTreeAVL *node){
    if((*node) != NULL){
        posOrder(&(*node)->left);
        posOrder(&(*node)->right);
        printf("%d ", (*node)->element.key);
    }
}

void inOrderCresc(PtrTreeAVL *node){
    if((*node) != NULL){
        inOrderCresc(&(*node)->left);
        printf("%d ", (*node)->element.key);
        inOrderCresc(&(*node)->right);
    }

}

void inOrderDecresc(PtrTreeAVL *node){
    if((*node) != NULL){
        inOrderDecresc(&(*node)->right);
        printf("%d ", (*node)->element.key);
        inOrderDecresc(&(*node)->left);
    }
}


bool pesquisaArvoreAVL(PtrTreeAVL *node);
void destruirArvoreAVL(PtrTreeAVL *node);

PtrTreeAVL getMinAux (PtrTreeAVL *node){//usado na remoção
    PtrTreeAVL Aux;
    if((*node)->left == NULL){
        Aux = (*node);
        (*node)=(*node)->right;
        return Aux;
    } else {
        return getMinAux(&(*node)->left);
    }
//    Aux = (*node);
//    while(Aux->left != NULL){
//        Aux = Aux->left;
//    }
//    (*node) = (*node)->right;
//    return (*node);
}
PtrTreeAVL getMaxAux (PtrTreeAVL *node) { //usado na remoção

    PtrTreeAVL Aux;
    if((*node)->right == NULL) {
        Aux = (*node);
        (*node) = (*node)->left;
        return Aux;
    } else {
        return getMaxAux(&((*node)->right));
    }
    //    Aux = (*node);
//    while(Aux->right != NULL){
//        Aux = Aux->right;
//    }
//    (*node) = (*node)->left;
//    return Aux;
}

bool removeAVL(PtrTreeAVL *node,int key){
    bool test;
    int he, hd;
    if((*node) == NULL){
        return false;
    }
    PtrTreeAVL Aux = NULL;
    if((*node)->element.key == key){
        if((*node)->left == NULL && (*node)->right != NULL){
            (*node) = (*node)->right;

        } else if((*node)->left != NULL && (*node)->right == NULL){//arvore direita NULA
            (*node) = (*node)->left;

        } else if((*node)->left == NULL && (*node)->right == NULL){//arvore esqueda NULA
            (*node) = NULL;

        } else if((*node)->left != NULL && (*node)->right != NULL){//((*node)->left != NULL && (*node)->right != NULL)
            Aux = getMinAux(&((*node)->right));
//            Aux = getMaxAux(&((*node)->left));
            (*node)->element = Aux->element;
            printf("Elemento Removido com Sucesso: %d\n",key);
        }
        free(Aux);

        return true;
    }

}

void imprimeArvoreAVLNivel(PtrTreeAVL *node){

}

#endif //ARVORESAVL_ARVOREAVL_H
