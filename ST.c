#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Item.h"
#include <math.h>

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
			if(strcmp(aux2->item->chave,palavra)>0)
			{
				auxDesloca=aux2;
				aux2=aux2->right;
			}
			else{
				if(strcmp(aux2->item->chave,palavra)<0)
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
				if(strcmp(auxDesloca->item->chave,palavra)>0){
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

void adicionaArvoreFreq(bTree **raiz, char *palavra, bTree *raizaux){
	bTree *auxratio = (bTree *) malloc(sizeof(bTree)), *aux = *raiz, *auxDesloca;
	Item *auxItem=NULL, *auxItem2=NULL, *auxlista, *auxlista2;
	if(!auxratio)printf("Não há espaço disponível!\n");
	else{
		
		
		while(strcmp(raizaux->item->chave, palavra)!=0)		//compara palavra na árvore de "dicionário"
		{
			if(strcmp(raizaux->item->chave, palavra)>0)raizaux=raizaux->right;
			else raizaux=raizaux->left;
		}
		auxratio->item = raizaux->item;
		while(aux){
			auxDesloca=aux;
			auxlista = auxDesloca->item;
			while(auxlista && strcmp(raizaux->item->chave,auxlista->chave))
			{
				auxlista2 = auxlista;
				auxlista = auxlista->prox;
			}
			if(auxlista && !strcmp(raizaux->item->chave,auxlista->chave))
			{
				if(auxlista == auxDesloca->item){
					auxlista = auxDesloca->item;
					auxDesloca->item = auxDesloca->item->prox;
					//free(auxlista);
				}
				else{
					auxlista = auxlista2;
					auxlista2 = auxlista2->prox;
					//free(auxlista);
				}
					
			}
			if(raizaux->item->freq > aux->item->freq)aux=aux->right;
			else{
				if(raizaux->item->freq < aux->item->freq)aux=aux->left;
				else{
					auxItem=auxDesloca->item;
					//free(auxratio);
					//auxItemRatio = (Item *) malloc(sizeof(Item));
					while(auxItem && strcmp(auxItem->chave,raizaux->item->chave)<0){
						auxItem2=auxItem;
						auxItem=auxItem->prox;
					}
					if(auxItem)
					{
						if(auxItem == auxDesloca->item) auxDesloca->item = raizaux->item;
						else auxItem2->prox = raizaux->item;
						raizaux->item->prox = auxItem;		
					}
					else auxItem2->prox = raizaux->item;
					break;
				}
			}
			
		}
		if(!auxItem && !auxItem2){
			auxratio->left=NULL;
			auxratio->right=NULL;
			if(!*raiz) *raiz = auxratio;
			else{
				if(auxratio->item->freq > auxDesloca->item->freq) auxDesloca->right= auxratio;
				else auxDesloca->left = auxratio;
			}
		}
		//else free(auxItem);
	}
}

/*void montaArvore(bTree *raiz, int max, int vez)
{
	if(vez<=1)
	{
		for(int i=vez;i<max;i++) printf("| "); 
		if(raiz)printf("\b-%s\n", raiz->item->chave);
		else printf("\b-NULL\n");
	}
	else
	{
		if(raiz)
		{
			for(int i=vez;i<max;i++) printf("| ");
			if(vez==max)printf("%s\n", raiz->item->chave);
			else printf("\b-%s\n", raiz->item->chave);
			if(raiz->left || raiz->right) montaArvore(raiz->left, max, (vez-1));
			if(raiz->left || raiz->right) montaArvore(raiz->right, max, (vez-1));
		}
	}
}

void imprimeArvore(bTree *raiz, int max)
{
	//int *vetaux = (int *)calloc((max-1),sizeof(int));
	montaArvore(raiz, max, max);
}

int *updateVB(int *vB, int h)
{
	int i;
	
	for(i=0; i<(h-1);i++){
		if(vB[i]>0)printf("| ");
		else printf("  ");
	}
}*/

void procuraPalavra(bTree *raiz, char *palavra){
	struct timeval antes , depois;
	int h=1, diff;
	
	gettimeofday(&antes , NULL);
	while(raiz && strcmp(raiz->item->chave,palavra))
	{
		if(strcmp(raiz->item->chave,palavra)>0) raiz=raiz->right;
		else raiz=raiz->left;
		h++;
	}
	gettimeofday(&depois , NULL);
	
	diff = ((depois.tv_sec - antes.tv_sec) * 1000000) + (depois.tv_usec - antes.tv_usec);
	
	printf("Palavra: %s\n", raiz->item->chave);
	printf("Frequencia: %d vez(es)\n", raiz->item->freq);
	printf("Altura: %d\n", h);
	printf("Tempo de execucao: %d ms\n", diff);
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
		(code % 2) ? printf("|") : printf(" ");
		trail(lvl - 1, (int) code/2);
	}
}

void imprimeArvore(int lvl, int max, int code, int override, bTree *raiz){
	if(lvl<=max){
		if (raiz) {
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			if(!lvl) printf("%s\n", raiz->item->chave);
			else printf("-%s\n", raiz->item->chave);
			imprimeArvore(lvl + 1, max, code + pow(2, lvl), 0, raiz->left );
			imprimeArvore(lvl + 1, max, code              , 1, raiz->right);
		}
		else{
			(override) ? trail(lvl, code + pow(2, lvl - 1)) : trail(lvl, code);
			printf("-NULL\n");
		}
	}
} 

