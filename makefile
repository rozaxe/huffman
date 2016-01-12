
all: huffman

huffman: main.o huffman.o io.o tree.o
	gcc -o huffman main.o huffman.o io.o tree.o

main.o: main.c
	gcc -c main.c

huffman.o: huffman.c
	gcc -c huffman.c

io.o: io.c
	gcc -c io.c

tree.o: tree.c
	gcc -c tree.c

clean:
	rm -rf huffman *.o
