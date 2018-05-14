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

Item *devolverItem(char *palavra, Item *registro){
	if(strcmp(palavra, registro->chave)) return registro;
	registro->freq++;
	return registro;
}
