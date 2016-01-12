
all: huffman

huffman: main.o huffman.o tree.o io.o
	gcc -o huffman main.o huffman.o tree.o io.o

main.o: main.c
	gcc -c main.c

huffman.o: huffman.c
	gcc -c huffman.c

tree.o: tree.c
	gcc -c tree.c

io.o: io.c
	gcc -c io.c

clean:
	rm -rf huffman *.o
