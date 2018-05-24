# Projeto 2 - Estrutura e Recuperação de Dados A
INDEXADOR E CONTADOR DE PALAVRAS

## Utilização
### Projeto Básico
Imprime uma lista com as N palavras mais frequentes no arquivo de entrada
```shell session
$ ./projeto2 -nNUMERO < ENTRADA.TXT
```
```shell session
$ ./projeto2 -n5 < tale.txt
7989 the
4931 and
4002 of
3460 to
2909 a
```
```shell session
$ ./projeto2 -n10 < tinyTale.txt
10 it
10 of
10 the
10 was
2 age
2 epoch
2 season
2 times
1 belief
1 best
```

### Utilizando arquivos para entrada e saída
Escreve as informações da árvore no arquivo designado com `-wFILENAME`
```shell session
$ ./projeto2 -nNUMERO -wFILENAME < ENTRADA.TXT
```

Carrega as informações da árvore do arquivo designado com `-rFILENAME` (não recebe um arquivo de entrada)
```shell session
$ ./projeto2 -nNUMERO -rFILENAME
```

Note que se ambas as opções sejam informadas simultaneamente, apenas a opção `-w` será avaliada.

### Buscando uma palavra específica
Exibe informações específicas referentes à palavra designada com `-sWORD`:
1. A palavra buscada
2. A frenquência encontrada
3. A sua altura na árvore
4. Tempo de busca em microsegundos
```shell session
$ ./projeto2 -nNUMERO -sWORD < ENTRADA.TXT
```

### Utilizando uma árvore AVL
Executa o programa utilizando uma **árvore AVL (árvore binária de busca balanceada)**
```shell session
$ ./projeto2 -nNUMERO -b < ENTRADA.TXT
```

### Impressão gráfica da árvore
Exibe a árvore graficamente até a altura designada com `-pMAX`, substituindo nós nulos por `NULL`
```shell session
$ ./projeto2 -nNUMERO -pMAX < ENTRADA.TXT
```
```shell session
$ ./projeto2 -nNUMERO -p4 < ENTRADA.TXT
raiz
|- filho da esquerda (altura 2)
||- filho da esquerda (altura 3)
|||- filho da esquerda (altura 4)
|||- filho da direita (altura 4)
||- filho da direita (altura 3)
| |- filho da esquerda (altura 4)
| |- filho da direita (altura 4)
|- filho da direita (altura 2)
 |- filho da esquerda (altura 3)
 ||- filho da esquerda (altura 4)
 ||- filho da direita (altura 4)
 |- filho da direita (altura 3)
  |- filho da esquerda (altura 4)
  |- filho da direita (altura 4)
```

## Links Úteis
[Trello](https://trello.com/b/pNI00Ayv/projeto-estruturas-2 "Trello")  
[Algoritmos para referência](https://algs4.cs.princeton.edu/30searching/ "Algorithms, 4th Edition by Robert Sedgewick and Kevin Wayne")
