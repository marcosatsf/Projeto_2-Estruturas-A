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

int verifica(Item *registro, char *palavra){
	Item *aux = registro, *aux2 = registro;
	if(!registro) return 0;
	if(!registro->prox)
	while(aux)
	{
		if(!strcmp(aux->chave,palavra)){
			aux2->prox = aux->prox;
			free(aux);
			return 1;
		}
		aux2=aux;
		aux=aux->prox;
	}
}

Item *devolverItem(char *palavra, Item *registro){
	if(strcmp(palavra, registro->chave))
	else registro->freq++;
	return registro;
}
