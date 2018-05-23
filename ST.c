#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Item.h"
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
};
typedef struct tipoArvore bTree;

void adicionaArvore(bTree **raiz, char *palavra)
{
	bTree *auxword= (bTree *)malloc(sizeof(bTree));
	bTree *aux2 = *raiz, *auxDesloca;
	if(!auxword) printf("Não há espaço disponível!\n");
	else
	{
		auxword->item = insereItem(palavra);
		while(aux2)
		{
			if(comparaPalavra(aux2->item,palavra)<0)
			{
				auxDesloca=aux2;
				aux2=aux2->right;
			}
			else{
				if(comparaPalavra(aux2->item,palavra)>0)
				{
					auxDesloca=aux2;
					aux2=aux2->left;
				}
				else{
					aux2->item->freq++;
					free(auxword->item);
					free(auxword);
					auxword=NULL;
					break;
				}
			}
		}
		if(auxword){
			auxword->left=NULL;
			auxword->right=NULL;
			if(!*raiz) *raiz = auxword;
			else
			{
				if(comparaPalavra(auxDesloca->item,palavra)<0){
					if(auxDesloca==*raiz) (*raiz)->right = auxword;
					else auxDesloca->right = auxword;
				}
				else{
					if(auxDesloca==*raiz) (*raiz)->left = auxword;
					else auxDesloca->left = auxword;
				}
			}	
		}
	}
}

void adicionaArvoreFreq(bTree **raiz, char *palavra){
	bTree *auxfreq= (bTree *)malloc(sizeof(bTree)), *aux2 = *raiz;
	if(!auxfreq) printf("Não há espaço disponível!\n");
	else
	{
		auxfreq->item = insereItem(palavra);
		while(aux2)
		{
			if(verifica(auxfreq->item, palavra)) limpalista();	//futura função para remover o item da lista ligada
			aux2 = aux2->prox;
		}
		auxfreq->left = NULL;
		auxfreq->right= NULL;
		if(*raiz) *raiz = auxfreq;
		else aux2 = auxfreq;
	}
}

void procuraPalavra(bTree *raiz, char *palavra){
	struct timeval antes , depois;
	int h=1, diff;
	
	gettimeofday(&antes , NULL);
	while(raiz && strcmp(raiz->item->chave,palavra))
	{
		if(strcmp(raiz->item->chave,palavra)<0) raiz=raiz->right;
		else raiz=raiz->left;
		//sleep(1);
		h++;
	}
	gettimeofday(&depois , NULL);
	
	diff = ((depois.tv_sec - antes.tv_sec) * 1000000) + (depois.tv_usec - antes.tv_usec);
	
	printf("Palavra: %s\n", raiz->item->chave);
	printf("Frequencia: %d vez(es)\n", raiz->item->freq);
	printf("Altura: %d\n", h);
	printf("Tempo de execucao: %d us\n", diff);
}

void salvaArquivo(bTree *raiz, char *palavra){//não terminada
	FILE *p;
	strcat(palavra,".dat");
	p = fopen(palavra, "wb");
	if(!p) printf("Erro na abertura do arquivo!\n");
	else{
		fwrite(raiz, sizeof(bTree), 1, p);
		fwrite(raiz->item, sizeof(Item), 1, p);
	}
	fclose(p);
}

void recuperaArquivo(bTree **raiz, char *palavra){//não terminada
	FILE *p;
	strcat(palavra,".dat");
	bTree *aux;
	p = fopen(palavra, "rb");
	if(!p) printf("Erro na abertura do arquivo!\n");
	else{
		aux = (bTree *) malloc(sizeof(bTree));
		aux->item = (Item *) malloc(sizeof(Item));
		fread(aux, sizeof(bTree), 1, p);
		fread(aux->item, sizeof(Item), 1, p);
		*raiz = aux;
	}
	fclose(p);
}

void trail(int lvl, int code){
	if (lvl) {
		(code % 2) ? printf("| ") : printf("  ");
		trail(lvl - 1, (int) code/2);
	}
}

void imprimeArvore(int lvl, int max, int code, int override, bTree *raiz){
	if(lvl<=max){
		if (raiz) {
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			if(!lvl) printf("%s\n", raiz->item->chave);
			else printf("\b- %s\n", raiz->item->chave);
			imprimeArvore(lvl + 1, max, code + pow(2, lvl), 0, raiz->left );
			imprimeArvore(lvl + 1, max, code              , 1, raiz->right);
		}
		else{
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			printf("\b- NULL\n");
		}
	}
} 

