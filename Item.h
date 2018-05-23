typedef struct tipoItem Item;

Item *insereItem(char *palavra);
int comparaPalavra(Item *registro, char *palavra);
Item *devolverItem(char *palavra, Item *registro);
