CC = gcc
CFLAGS = -Wall -g
LIBS = -lrt

all: libclaves.so servidor cliente

libclaves.so: claves.o
	$(CC) -shared -o libclaves.so claves.o

servidor: servidor.o libclaves.so
	$(CC) $(CFLAGS) -o servidor servidor.o -L. -lclaves $(LIBS)

cliente: cliente.o libclaves.so
	$(CC) $(CFLAGS) -o cliente cliente.o -L. -lclaves $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o servidor cliente libclaves.so