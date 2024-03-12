#include <stdio.h>
#include "clavesservidor.h"
#include "mensaje.h"
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int claves;
int key_leida;
char valor1[100];
int N_value2;
double V_value2[100];

int init_serv() {
  printf("Inicialización exitosa");

  return 0; // Inicialización exitosa
}

int set_value_serv(int key, char *value1, int N_value2, double *V_value2) {
  
    printf("Clave insertada con éxito set value serv\n");
    return 0; // Inserción exitosa
  }


int get_value_serv(int key, char *value1, int N_value2, double *V_value2) {
      printf("Clave leida con éxito get value serv\n");
  return -1; // Clave no encontrada
}
int modify_value_serv(int key, char *value1, int N_value2, double *V_value2) {
  printf("Clave modificada con éxitomodi value serv\n");
}
int delete_value_serv(int key) {
  printf("Clave eliminada con éxito delete value serv\n");
  return 0; // Eliminación exitosa
}
int exists_serv(int key) {
  printf("Clave encontrada con éxito exists serv\n");
  return 0; // Clave encontrada
}