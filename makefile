index:
	gcc -c Item.h
	gcc -g -c Item.c
	gcc -c ST.h
	gcc -g -c ST.c -lm
	gcc -g -c main.c
	gcc -g -o projeto2 Item.o ST.o main.o -lm
	clear
	echo "Compilado com sucesso!"
clean:
	rm -rf Item.h.gch
	rm -rf ST.h.gch
	rm -rf Item.o
	rm -rf ST.o
	rm -rf main.o
	rm -rf ProjetoIndexador
	clear
