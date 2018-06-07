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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ST.h"
#include "Item.h"

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
	bTree *rootWord=NULL;
	int n, vetctrl[6]={0};
	char word[50];
	for(int i=1;i<argc;i++)
		switch(argv[i][1])
		{
			case 'n':vetctrl[0]=1;
			break;
			case 'w':vetctrl[1]=1;
			break;
			case 'r':vetctrl[2]=1;
			break;
			case 's':vetctrl[3]=1;
			break;
			case 'p':vetctrl[4]=1;
			break;
			case 'b':vetctrl[5]=1;
			break;
		}
	if(vetctrl[1]&&vetctrl[2])vetctrl[2]=0;
	if(vetctrl[0]){
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
		if(vetctrl[1])
		{
			salvaArquivo(rootWord, argv[i]+2);
		}
		if(vetctrl[2])
		{
			recuperaArquivo(&rootWord, argv[i]+2);
		}
		if(vetctrl[3])
		{
			procuraPalavra(rootWord, argv[i]+2);
		}
		if(vetctrl[4])
		{
			vetctrl[4]=1;
			n = contaN(argv[i], 2);
			//imprimeArvore(rootWord, n);
			imprimeArvore(0,n,0,0,rootWord);
		}
		if(vetctrl[5])
		{
			//Funções de AVL
		}
		
	}
	free(rootWord);
	free(prim);

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

