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

void adicionaLista(no **primeiro, char *palavra)
{
	if (!(*primeiro)) {
		no *aux = (no *)malloc(sizeof(no));
		if (!aux) {
			printf("ERRO\n");
		} else {
			strcpy(aux->chave, palavra);
			aux->prox = NULL;
			(*primeiro) = aux;
		}
	} else {
		no *aux = (*primeiro);
		no *aux2 = (*primeiro);
		while (aux) {
			if (strcmp(aux->chave, palavra) > 0) { //continuar andando
				if (aux != (*primeiro)) aux2 = aux2->prox;
				aux = aux->prox;
			} else {
				no *aux3 = (no *)malloc(sizeof(no));
				if (!aux3) { printf("ERRO\n"); } else {
					strcpy(aux3->chave, palavra);
					aux3->prox = aux;
					aux2->prox = aux3;
				}
			}
		}
		no *aux3 = (no *)malloc(sizeof(no));
		if (!aux3) { printf("ERRO\n"); } else {
			strcpy(aux3->chave, palavra);
			aux3->prox = NULL;
			aux->prox = aux3;
		}
	}

	/*	
	no *aux = (*no) malloc(sizeof(no));
	if (!aux) { printf("ERRO\n"); } else {
		aux->prox = (*primeiro);
		aux->chave = palavra;
		(*primeiro) = aux;
	}
	*/
}

no **adicionaBloco(bloco **primeiro, int freq)
{
	if (!(*primeiro)) {
		bloco *aux = (bloco *)malloc(sizeof(bloco));
		if (!aux) { printf("ERRO\n"); } else {
			aux->freq = freq;
			aux->prim = NULL;
			aux->proxBloco = NULL;
			(*primeiro) = aux;
			return &(aux->prim);
		}
	} else {
		bloco *atual = (*primeiro);
		while (atual) {
			if (atual->freq == freq) return &(atual->prim);
			atual = atual->proxBloco;
		}
		atual = (bloco *)malloc(sizeof(bloco));
		if (!atual) { printf("ERRO\n"); } else {
			bloco *aux = (*primeiro);
			while (aux->proxBloco) aux = aux->proxBloco; 
			atual->freq = freq;
			atual->prim = NULL;
			atual->proxBloco = NULL;
			aux->proxBloco = aux;
			return &(atual->prim);
		}
	}
}

void montaListas(bTree *raiz, bloco **primeiro)
{
	if (raiz) {
		adicionaLista(adicionaBloco((*primeiro), raiz->item->freq), raiz->item->chave);
		montaListas(raiz->left, (*primeiro));
		montaListas(raiz->right, (*primeiro));
	}
}

void testalista(bloco *primeiro)
{
	while (primeiro) {
		printf("No de frequencia %i: ", primeiro->freq);
		no* aux = primeiro->prim;
		while (aux) {
			printf("[%s] ", aux->chave);
			aux = aux->prox;
		}
		printf("\n");
		primeiro = primeiro->proxBloco;
	}
}

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
/*
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
*/
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

