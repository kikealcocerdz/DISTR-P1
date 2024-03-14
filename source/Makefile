all:
	gcc -c -fPIC claves.c -o claves.o
	gcc -shared -o libclaves.so claves.o
	gcc cliente.c libclaves.so -o cliente
	gcc clavesservidor.c servidor.c -o servidor
