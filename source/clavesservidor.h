#ifndef CLAVES_H
#define CLAVES_H

#include <stdio.h>

int init_serv();
int set_value_serv(int key, char *value1, int N_value2, double *V_value2, char *clavescliente);
int get_value_serv(int key, char *value1, int N_value2, double *V_value2);
int modify_value_serv(int key, char *value1, int N_value2, double *V_value2);
int delete_value_serv(int key);
int exists_serv(int key);

#endif // CLAVES_H


//USAR gcc clavesservidor.c servidor.c -o servidor
