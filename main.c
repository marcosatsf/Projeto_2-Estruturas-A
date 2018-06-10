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
#include "STb.h"
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
	int height;
};
typedef struct tipoArvore bTree;

int contaN(char *vet, int pos);
void printcomand();

int main(int argc, char **argv)
{
	bTree *rootWord=NULL;
	bloco *prim = NULL;
	int n,pNum, vetctrl[6]={0};
	char word[50], nomeArq[50];
	for(int i=1;i<argc;i++)
		switch(argv[i][1])
		{
			case 'n':vetctrl[0]=1;
			n = contaN(argv[i], 2);
			break;
			case 'w':vetctrl[1]=1;
			strcpy(nomeArq, argv[i]+2);
			break;
			case 'r':vetctrl[2]=1;
			strcpy(nomeArq, argv[i]+2);
			break;
			case 's':vetctrl[3]=1;
			strcpy(nomeArq, argv[i]+2);
			break;
			case 'p':vetctrl[4]=1;
			pNum = contaN(argv[i], 2);
			break;
			case 'b':vetctrl[5]=1;
			break;
		}
	if(vetctrl[1]&&vetctrl[2])vetctrl[2]=0;

	else{
		if(vetctrl[0]){
			if(vetctrl[2]) iniciaRecuperaArquivo(&rootWord, nomeArq);
			else{
				while(scanf("%s", word) != EOF){
					if(vetctrl[5])
						adicionaArvore(&rootWord, word);
					else
						insereAVL(&rootWord, word);
					//adicionaArvoreFreq(&rootRatio , word, rootWord);
				}
			}
			montaListas(rootWord, &prim);
			//testalista(prim);
			imprimeN(prim, n);
			if(vetctrl[1]) iniciaSalvaArquivo(rootWord, nomeArq);
			if(vetctrl[3]) procuraPalavra(rootWord, nomeArq);
			if(vetctrl[4]) imprimeArvore(0,pNum,0,0,rootWord);
			/*if(vetctrl[5])
			{
				//Funções de AVL, provavelmente será necessário substituir o comando -n, entao só colocar a parte que executa o -n como um else 
			}*/
		
		}
		else printf("Nao foi encontrado o argumento -n.\n");
		free(rootWord);
		free(prim);

		return 0;
	}
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
void printcomand(){
	printf("Argumentos possiveis neste programa:\n");
	printf("-nNUMERO < NOME_DO_ARQUIVO.txt: Devolve as palavras mais frequentes de um texto(obrigatorio para execucao);\n");
	printf("-wNOME_DO_ARQUIVO: Escreve em um arquivo binario as palavras da tabela de simbolos e suas respectivas frequencias;\n");
	printf("-rNOME_NO_ARQUIVO: Le de um arquivo binario as palavras e suas respectivas frequencias;\n");
	printf("-sPALAVRA: Procura a PALAVRA na arvore, devolvendo sua altura, frequencia e o tempo de busca;\n");
	printf("-b: Balanceia a arvore binaria;\n");
	printf("-pNUMERO: Imprime a arvore binaria de altura NUMERO.\n");
}

