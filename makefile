
all: huffman

huffman: main.o huffman.o io.o
	gcc -o huffman main.o huffman.o io.o

main.o: main.c
	gcc -c main.c

huffman.o: huffman.c
	gcc -c huffman.c

io.o: io.c
	gcc -c io.c

clean:
	rm -rf huffman *.o
