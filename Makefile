CC=g++
CFLAGS=-O3 -std=c++11 -Wall -Iinclude -c -g
LDFLAGS=
EXECUTABLE=ipmt


pmt: main.o util.o lz78.o
	mkdir -p bin
	$(CC) main.o util.o lz78.o -o bin/ipmt
	rm *.o

#objetos dos algoritmos

lz78.o:
	$(CC) $(CFLAGS) src/lz78.cpp

#objetos padrao
main.o: util.o
	$(CC) $(CFLAGS) src/main.cpp

util.o:
	$(CC) $(CFLAGS) src/util.cpp

clean:
	rm -rf *.o bin
