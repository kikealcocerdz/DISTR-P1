#ifndef CLAVES_H
#define CLAVES_H

#include <stdio.h>

int init_serv(char *clavescliente);
int set_value_serv(int key, char *value1, int N_value2, double *V_value2, char *clavescliente);
int get_value_serv(int key, char *value1, int N_value2, double *V_value2, char *clavescliente);
int modify_value_serv(int key, char *value1, int N_value2, double *V_value2, char *clavescliente);
int delete_value_serv(int key, char *clavescliente);
int exists_serv(int key, char *clavescliente);

#endif // CLAVES_H


//USAR gcc clavesservidor.c servidor.c -o servidor
/*
gcc -c -fPIC claves.c -o claves.o
gcc -shared -o libclaves.so claves.o
gcc cliente.c libclaves.so -o cliente
gcc clavesservidor.c servidor.c -o servidor
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/source/libclaves.so

*/