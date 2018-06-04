/*
Integrante 1 - Nome: Bruno Guilherme Marini Spirlandeli 	RA: 17037607
Integrante 2 - Nome: Caio Lima e Souza Della Torre Sanches 	RA: 17225285
Integrante 3 - Nome: Gabriela Nelsina Vicente 			RA: 17757089
Integrante 4 - Nome: Marcos Aurélio Tavares de Sousa Filho 	RA: 17042284
Resultados obtidos:
Projeto básico: __% concluído - Obs:
( ) Opcional 1 - Obs: 
(X) Opcional 2 - Obs: 
( ) Opcional 3 - Obs: 
(X) Opcional 4 - Obs: Realizado com sucesso
*/

#define TRAILSIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ST.h"
#include "Item.h"

struct tipoTrail {
	char trail[TRAILSIZE];
	//int size;
	int cpos;
};
typedef struct tipoTrail trailing;

struct tipoItem {
	char chave[50];
	int freq;
};
typedef struct tipoItem Item;

struct tipoArvore {
	struct tipoItem *item;
	struct tipoArvore *left;
	struct tipoArvore *right;
};
typedef struct tipoArvore bTree;

int contaN(char *vet, int pos);

int main(int argc, char **argv)
{
	bTree *rootWord=NULL, *rootRatio=NULL;
	int n;
	char word[50];
	for(int i=1;i<argc;i++)
	{
		if(argv[i][1]=='n' && argv[i][2]>'0' && argv[i][2]<='9')
		{
			n = contaN(argv[i], 2);
			while(scanf("%s", word) != EOF)
			{
				adicionaArvore(&rootWord, word);
				//adicionaArvoreFreq(&rootRatio , word, rootWord);
			}
			bloco *prim = NULL;
			montaListas(rootWord, &prim);
			//testalista(prim);
			imprimeN(prim, n);
		}
		if(argv[i][1]=='w') salvaArquivo(rootWord, argv[i]+2);
		else if(argv[i][1]=='r') recuperaArquivo(&rootWord, argv[i]+2);
		if(argv[i][1]=='s') procuraPalavra(rootWord, argv[i]+2);
		if(argv[i][1]=='p' && argv[i][2]>'0' && argv[i][2]<='9')
		{
			trailing *t = (trailing *)malloc(sizeof(trailing));
			//strcpy(t->trail, "|");
			//t->cpos = 1;
			//t->size = 1;
			n = contaN(argv[i], 2);
			//imprimeArvore(rootWord, n);
			
			//imprimeArvore(0,n,0,0,rootWord);
			trailBeta(0, n, t,  rootWord);			
			free(t);
		}
		//if(argv[i][1]=='b') em andamento
	}
	free(rootWord);

	return 0;
}

int contaN(char *vet, int pos)
{
	int num=1, tot=0;
	while(vet[pos+1]!='\0')	pos++;
	for(int i=2;i<pos;i++)	num*=10;
	for(int i=2;i<=pos;i++)
	{
		tot+=((vet[i]-'0')*num);
		num/=10;
	}
	return tot;
}

