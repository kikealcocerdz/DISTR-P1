#ifndef CLAVES_H
#define CLAVES_H

#include <stdio.h>
#include "mensaje.h"

void init_serv(struct respuesta *res);
void set_value_serv(int key, char *value1, int N_value2, char *V_value2, struct respuesta *res);
void get_value_serv(int key, char *value1, int *N_value2, char *V_value2, struct respuesta *res);
void modify_value_serv(int key, char *value1, int N_value2, char *V_value2, struct respuesta *res);
void delete_value_serv(int key, struct respuesta *res);
void exists_serv(int key, struct respuesta *res);

#endif // CLAVES_H

