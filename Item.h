#include<stdio.h>

typedef struct tipoItem Item;

Item *insereItem(char *palavra);
Item *alocaItem();
int comparaPalavra(Item *registro, char *palavra);
int comparaPalavraRegistros(Item *registro1, Item *registro2);
int verifica(Item *registro, char *palavra);
Item *devolverItem(char *palavra, Item *registro);
void escreveEmArquivo(Item *registro,FILE **f);
