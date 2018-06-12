#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tipoItem {
	char chave[50];
	int freq;
	struct tipoItem *prox;
};
typedef struct tipoItem Item;

Item *insereItem(char *palavra){
	Item *auxItem = (Item *) malloc(sizeof(Item));
	if(!auxItem) return NULL;
	strcpy(auxItem->chave, palavra);
	auxItem->freq=1;
	auxItem->prox = NULL; 
	return auxItem;
}

Item *alocaItem(){
	Item *alocador = (Item *) malloc(sizeof(Item));
	return alocador;
}

int comparaPalavra(Item *registro, char *palavra){
	return strcmp(registro->chave, palavra);
}

int comparaPalavraRegistros(Item *registro1, Item *registro2){
	return strcmp(registro1->chave, registro2->chave);
}



Item *devolverItem(char *palavra, Item *registro){
	if(!strcmp(palavra, registro->chave)) registro->freq++;
	return registro;
}

void escreveEmArquivo(Item *registro,FILE **f){
	fwrite(registro, sizeof(Item), 1, *f);
}
