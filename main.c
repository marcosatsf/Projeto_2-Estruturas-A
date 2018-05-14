#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ST.h"
#include "Item.h"

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
		}
		if(argv[i][1]=='w') salvaArquivo(rootWord, argv[i]+2);
		else if(argv[i][1]=='r') recuperaArquivo(&rootWord, argv[i]+2);
		if(argv[i][1]=='s') procuraPalavra(rootWord, argv[i]+2);
		if(argv[i][1]=='p' && argv[i][2]>'0' && argv[i][2]<='9')
		{
			n = contaN(argv[i], 2);
			//imprimeArvore(rootWord, n);
			tree(0,n,0,0,rootWord);
		}
		if(argv[i][1]=='b') //em andamento
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
