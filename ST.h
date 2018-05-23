typedef struct tipoItem Item;
typedef struct tipoArvore bTree;

void adicionaArvore(bTree **raiz, char *palavra);
void adicionaArvoreFreq(bTree **raiz, char *palavra, bTree *raizaux);
//int *updateVB(int *vB, int h);
void procuraPalavra(bTree *raiz, char *palavra);
void salvaArquivo(bTree *raiz, char *palavra);
void recuperaArquivo(bTree **raiz, char *palavra);
void trail(int lvl, int code);
void imprimeArvore(int lvl, int max, int code, int override, bTree *raiz);
