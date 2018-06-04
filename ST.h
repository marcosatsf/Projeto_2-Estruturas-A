typedef struct tipoItem Item;
typedef struct tipoArvore bTree;
typedef struct tipoTrail trailing;

typedef struct tipoNo no;
typedef struct tipoBloco bloco;

void adicionaArvore(bTree **raiz, char *palavra);
////void adicionaArvoreFreq(bTree **raiz, char *palavra, bTree *raizaux);
//int *updateVB(int *vB, int h);
void procuraPalavra(bTree *raiz, char *palavra);
void salvaArquivo(bTree *raiz, char *palavra);
void recuperaArquivo(bTree **raiz, char *palavra);
void trail(int lvl, double code);
void imprimeArvore(int lvl, int max, double code, int override, bTree *raiz);

void trailBeta(int c, int max, trailing *t, bTree *raiz);
void push(trailing *t, char c);
char pop(trailing *t);

void adicionaLista(no **primeiro, char *palavra);
no **adicionaBloco(bloco **primeiro, int freq);
void montaListas(bTree *raiz, bloco **primeiro);
void testalista(bloco *primeiro);
void imprimeN(bloco *primeiro, int n);
