# Makefile for building cliente, servidor, and libclaves.so

all: cliente servidor

servidor: clavesservidor.c servidor.c
	gcc clavesservidor.c servidor.c -o servidor

libclaves.so: claves.o
	gcc -shared -o libclaves.so claves.o

claves.o: claves.c
	gcc -c -fPIC claves.c -o claves.o

clean:
	rm -f cliente servidor libclaves.so *.o
