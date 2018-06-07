typedef struct tipoItem Item;

Item *insereItem(char *palavra);
Item *alocaItem();
int comparaPalavra(Item *registro, char *palavra);
int verifica(Item *registro, char *palavra);
Item *devolverItem(char *palavra, Item *registro);
