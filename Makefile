CC=g++
CFLAGS=-std=c++11 -Wall -Iinclude -c -g -O3
LDFLAGS=
EXECUTABLE=ipmt


pmt: main.o util.o ez78.o
	mkdir -p bin
	$(CC) main.o util.o ez78.o -o bin/ipmt
	rm *.o

#objetos dos algoritmos

ez78.o:
	$(CC) $(CFLAGS) src/ez78.cpp

#objetos padrao
main.o: util.o
	$(CC) $(CFLAGS) src/main.cpp

util.o:
	$(CC) $(CFLAGS) src/util.cpp

clean:
	rm -rf *.o bin
