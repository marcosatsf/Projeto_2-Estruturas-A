#include<stdio.h>

typedef struct tipoItem Item;
typedef struct tipoArvore bTree;

typedef struct tipoNo no;
typedef struct tipoBloco bloco;

int alturaAVL (bTree *raiz);
int fatBalanceamento (bTree *raiz);
int maior (int x, int y);
void rotacaoRR(bTree **raiz);
void rotacaoLL(bTree **raiz);
void rotacaoRL(bTree **raiz);
void rotacaoLR(bTree **raiz);
int adicionaAVL(bTree **raiz, char *palavra);
void insereAVL(bTree **raiz, char *palavra);

