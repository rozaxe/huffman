
all: huffman

huffman: io.o huffman.o
	gcc -o huffman io.o huffman.o

io.o: io.c
	gcc -c io.c

huffman.o: huffman.c
	gcc -c huffman.c

clean:
	rm -rf huffman *.o
