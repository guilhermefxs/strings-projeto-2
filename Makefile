CC=g++
CFLAGS=-O3 -std=c++14 -Wall -Iinclude -c -g
LDFLAGS=
EXECUTABLE=ipmt


ipmt: main.o util.o lz78.o sufixArray.o
	mkdir -p bin
	$(CC) main.o util.o lz78.o sufixArray.o -o bin/ipmt
	rm *.o

#objetos dos algoritmos

lz78.o:
	$(CC) $(CFLAGS) src/lz78.cpp

sufixArray.o:
	$(CC) $(CFLAGS) src/sufixArray.cpp

#objetos padrao
main.o: util.o
	$(CC) $(CFLAGS) src/main.cpp

util.o:
	$(CC) $(CFLAGS) src/util.cpp

clean:
	rm -rf *.o bin
