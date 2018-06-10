#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Item.h"
#include "ST.h"
#include <math.h>
#include <unistd.h>

struct tipoItem {
	char chave[50];
	int freq;
	struct tipoItem *prox;
};
typedef struct tipoItem Item;

struct tipoArvore {
	struct tipoItem *item;
	struct tipoArvore *left;
	struct tipoArvore *right;
	int height;
};
typedef struct tipoArvore bTree;

struct tipoNo {
	char chave[50];
	struct tipoNo *prox;
};
typedef struct tipoNo no;

struct tipoBloco {
	int freq;
	struct tipoBloco *proxBloco;
	struct tipoNo *prim;
};
typedef struct tipoBloco bloco;

int alturaAVL (bTree *raiz) 
{
	if (!raiz)
		return -1;
	else
		return (raiz->height);
}

int fatBalanceamento (bTree *raiz)
{
	int bal;
	bal = (alturaAVL(raiz->left)-alturaAVL(raiz->right));
	if (bal>=0)
		return bal;
	else 
		return -1 * bal;
}

int maior (int x, int y)
{
	if (x>y)
		return x;
	else
		return y;
}

void rotacaoRR(bTree **raiz)
{
	bTree *aux = (*raiz)->right;
	(*raiz)->right = aux->left;
	aux->left = *raiz;
	(*raiz)->height = 1 + maior(alturaAVL ((*raiz)->right),
				    alturaAVL ((*raiz)->left));
	aux->height = 1 + maior(alturaAVL (aux->right), (*raiz)->height);
	*raiz = aux;
}

void rotacaoLL(bTree **raiz)
{
	bTree *aux = (*raiz)->left;
	(*raiz)->left = aux->right;
	aux->right = *raiz;
	(*raiz)->height = 1 + maior(alturaAVL ((*raiz)->left),
				    alturaAVL ((*raiz)->right));
	aux->height = 1 + maior(alturaAVL (aux->left), (*raiz)->height);
	*raiz = aux;
}

void rotacaoRL(bTree **raiz)
{
	rotacaoLL(&(*raiz)->right);
	rotacaoRR(&(*raiz));
}

void rotacaoLR(bTree **raiz)
{
	rotacaoRR(&(*raiz)->left);
	rotacaoLL(&(*raiz));
}

int adicionaAVL(bTree **raiz, char *palavra)
{
	int result;
	bTree *aux2 = *raiz, *auxword;
	if((*raiz)==NULL){
		bTree *auxword = (bTree *)malloc(sizeof(bTree));
		if(!auxword) return -1;//printf("Não há espaço disponível!\n");
		else
		{
			auxword->item = insereItem(palavra);
			auxword->height = 0;
			auxword->right = NULL;
			auxword->left = NULL;
			*raiz = auxword;
			return 1;		
		}
	}
	else{
		bTree *aux2 = *raiz;
		if(comparaPalavra(aux2->item,palavra)>0){
			if((result = adicionaAVL (&(aux2->left), palavra))==1){
				if(fatBalanceamento(aux2)>=2){
					if(comparaPalavra(aux2->left->item,palavra)>0)
						rotacaoLL(raiz);
					else
						rotacaoLR(raiz);
				}
			}
		}
		else{
			if(comparaPalavra(aux2->item,palavra)<0){
				if((result = adicionaAVL (&(aux2->right), palavra))==1){
					if(fatBalanceamento(aux2)>=2){
						if(comparaPalavra(aux2->right->item,palavra)<0)
							rotacaoRR(&(*raiz));
						else
							rotacaoRL(&(*raiz));
					}
				}
			}
			else{
				aux2->item = devolverItem(palavra,aux2->item);
				return 0;
			}
		}
		aux2->height = maior(alturaAVL(aux2->left), alturaAVL(aux2->right))+1;
		return result;
	}
}

void insereAVL(bTree **raiz, char *palavra)
{
	int result = adicionaAVL(&(*raiz), palavra);
	if (result == -1)
		printf("Não há espaço disponível!\n");
}

