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

void adicionaLista(no **primeiro, char *palavra)
{
	if (!(*primeiro)) {
		//printf("Got null pointer to list\n");
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
		int foundit = 0;
		while (aux && foundit == 0) {
			//printf("Current word is %s\n", aux->chave);
			if (strcmp(aux->chave, palavra) < 0) { //continuar andando
				//printf("Will move another step\n");
				if (aux != (*primeiro)) aux2 = aux2->prox;
				aux = aux->prox;
			} else {
				no *aux3 = (no *)malloc(sizeof(no));
				if (!aux3) { printf("ERRO\n"); } else {
					if (aux == (*primeiro)) {
						//printf("Was first pos\n");
						strcpy(aux3->chave, palavra);
						aux3->prox = aux;
						(*primeiro) = aux3;
						//aux2->prox = aux3;
						foundit = 1;
					} else {
						//printf("WASNT first pos\n");
						strcpy(aux3->chave, palavra);
						aux3->prox = aux;
						aux2->prox = aux3;
						//(*primeiro) = aux3;
						foundit = 1;
					}
				}
			}
		}
		if (foundit == 0) {
			//printf("Adding at last pos");
			no *aux3 = (no *)malloc(sizeof(no));
			if (!aux3) { printf("ERRO\n"); } else {
				strcpy(aux3->chave, palavra);
				aux3->prox = NULL;
				aux2->prox = aux3;
			}
		}
	}
}

no **adicionaBloco(bloco **primeiro, int freq)
{
	//printf("Entrou na funcao\n");
	bloco *teste = (*primeiro);
	if (teste == NULL) {
		//printf("Null blocks!\n");
		bloco *aux = (bloco *)malloc(sizeof(bloco));
		if (!aux) { printf("ERRO\n"); } else {
			aux->freq = freq;
			aux->prim = NULL;
			aux->proxBloco = NULL;
			(*primeiro) = aux;
			return &(aux->prim);
		}
	} else {
		//printf("Found existing blocks\n");
		bloco *atual = (*primeiro);
		bloco *aux2 = (*primeiro);
		//int i = 0;
		while (atual != NULL) {
			if (atual->freq > freq) {
				if (atual != (*primeiro)) aux2 = aux2->proxBloco;
				atual = atual->proxBloco;
			} else if (atual->freq == freq) {
				return &(atual->prim);
			} else { // atual < freq
				bloco *aux = (bloco *)malloc(sizeof(bloco));
				if (!aux) { printf("ERRO\n"); } else {
				aux->freq = freq;
				aux->prim = NULL;
					if (atual == (*primeiro)) {
						aux->proxBloco = (*primeiro);
						(*primeiro) = aux;
						return &(aux->prim);
					} else {
						aux->proxBloco = atual;
						aux2->proxBloco = aux;
						return &(aux->prim);
					}
				}
			}
		}
	}
	bloco *aux2 = (*primeiro); //DEBUG ONLY
	bloco *aux = (bloco *)malloc(sizeof(bloco));
	if (!aux) { printf("ERRO\n"); } else {
		aux->freq = freq;
		aux->prim = NULL;
		aux2->proxBloco = aux;
		return &(aux->prim);
	}
}

void testalista(bloco *primeiro)
{
	printf("----------------------------------------------\n");
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
	printf("----------------------------------------------\n");
}

void imprimeN(bloco *primeiro, int n)
{
	no *atual = primeiro->prim;
	while (primeiro && atual && n) {
		printf("%i %s\n", primeiro->freq, atual->chave);
		if (n > 0) {
			if (!(atual->prox)) {
				primeiro = primeiro->proxBloco;
				if (primeiro) atual = primeiro->prim;
			} else atual = atual->prox;
		}
		n--;
	}
}

void montaListas(bTree *raiz, bloco **primeiro)
{
	if (raiz) {
		//printf("Adding %s (%i)\n", raiz->item->chave, raiz->item->freq);
		no **aux = adicionaBloco(primeiro, raiz->item->freq);
		//printf("Got the list pointer\n");
		adicionaLista(aux, raiz->item->chave);
		//testalista((*primeiro));
		montaListas(raiz->left, primeiro);
		montaListas(raiz->right, primeiro);
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
					aux2->item = devolverItem(palavra,aux2->item);
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
	while(raiz && comparaPalavra(raiz->item,palavra))
	{
		if(comparaPalavra(raiz->item,palavra)<0) raiz=raiz->right;
		else raiz=raiz->left;
		h++;
	}
	gettimeofday(&depois , NULL);
	
	diff = ((depois.tv_sec - antes.tv_sec) * 1000000) + (depois.tv_usec - antes.tv_usec);
	
	if(raiz){
	printf("Palavra: %s\n", raiz->item->chave);
	printf("Frequencia: %d vez(es)\n", raiz->item->freq);
	printf("Altura: %d\n", h);
	printf("Tempo de execucao: %d us\n", diff);
	}
	else printf("A palavra %s nao foi encontrada!\n", raiz->item->chave);
}

void salvaArquivo(bTree *raiz,FILE *p){
	if(raiz)
	{
		escreveEmArquivo(raiz->item,&p);
		salvaArquivo(raiz->left,p);
		salvaArquivo(raiz->right,p);
	}	
}

void iniciaSalvaArquivo(bTree *raiz, char* palavra){
	FILE *pont;
	strcat(palavra,".dat");
	pont = fopen(palavra, "wb");
	if(!pont) printf("Erro na abertura do arquivo!\n");
	else salvaArquivo(raiz,pont);
	fclose(pont);
}

void recuperaArquivo(bTree **raiz, bTree **alocada){
	if(!*raiz) *raiz = *alocada;
	else{
		if(comparaPalavraRegistros((*raiz)->item,(*alocada)->item)<0)recuperaArquivo(&(*raiz)->right,&(*alocada));
		else recuperaArquivo(&(*raiz)->left,&(*alocada));
	}
}

void iniciaRecuperaArquivo(bTree **raiz, char *palavra){
	FILE *pont;
	strcat(palavra,".dat");
	pont = fopen(palavra, "r+b");
	if(!pont) printf("Erro na abertura do arquivo!\n");
	else{
		bTree *aux;
		while(!feof(pont))
		{
			aux = (bTree *) malloc(sizeof(bTree));
			if(!aux){
				printf("Heap overflow!\n");
				break;
			}
			aux->item = alocaItem();
			if(!aux->item){
				printf("Heap overflow!\n");
				break;
			}
			aux->left=NULL,aux->right=NULL;
			fread(aux->item, sizeof(Item), 1, pont);
			recuperaArquivo(&(*raiz), &aux);
			
		}
		fclose(pont);
	}
	
}

void trail(int lvl, double code){
	if (lvl) {
		((long long int)code % 2) ? printf("| ") : printf("  ");
		trail(lvl - 1, (long long int) code/2);
	}
}

void imprimeArvore(int lvl, int max, double code, int override, bTree *raiz){
	if(lvl<=max){
		if (raiz) {
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			if(!lvl) printf("%s (%i)\n", raiz->item->chave, raiz->item->freq);
			else printf("\b- %s (%i)\n", raiz->item->chave, raiz->item->freq);
			imprimeArvore(lvl + 1, max, code + pow(2, lvl), 0, raiz->left );
			imprimeArvore(lvl + 1, max, code              , 1, raiz->right);
		}
		else{
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			printf("\b- NULL\n");
		}
	}
}

