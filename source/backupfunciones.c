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
  claves = open("claves.txt", "a");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  fclose(claves);
  printf("Inicialización exitosa");
  return 0; // Inicialización exitosa
}

int set_value_serv(int key, char *value1, int N_value2, double *V_value2) {
  claves = open("claves.txt", "a");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  while (fscanf(claves, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
    if (key_leida == key) {
      return -1; // Clave encontrada,error ya que debe ser unica
    }
    fprintf(claves, "%d %s %d\n", key, value1, N_value2);
    fclose(claves);
    printf("Clave insertada con éxito");

        return 0; // Inserción exitosa
  }
}

int get_value_serv(int key, char *value1, int N_value2, double *V_value2) {
  claves = open("claves.txt", "r");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  while (fscanf(claves, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
    if (key_leida == key) {
      strcpy(value1, valor1);
      return 0; // Lectura exitosa
      printf("Clave leida con éxito", value1, N_value2, V_value2)
    }
  }
  fclose(claves);
  return -1; // Clave no encontrada
}
int modify_value_serv(int key, char *value1, int N_value2, double *V_value2) {
  claves = open("claves.txt", "r+");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  while (fscanf(claves, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
    if (key_leida == key) {
      fseek(claves, -strlen(valor1) - 1, SEEK_CUR);
      fprintf(claves, "%s", value1);
      return 0; // Modificación exitosa
    }
  }
  fclose(claves);
  return -1; // Clave no encontrada
}

int delete_value_serv(int key) {
  claves = open("claves.txt", "r+");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  while (fscanf(claves, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
    if (key_leida == key) {
      fseek(claves, -strlen(valor1) - 1, SEEK_CUR);
      fprintf(claves, "%s", " ");
      return 0; // Eliminación exitosa
    }
  }
  fclose(claves);
  return -1; // Clave no encontrada
}
int exists_serv(int key) {
  claves = open("claves.txt", "r");
  if (claves == NULL) {
    return -1; // Error al abrir el archivo
  }
  while (fscanf(claves, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
    if (key_leida == key) {
      return 0; // Clave encontrada
    }
  }
  fclose(claves);
  return -1; // Clave no encontrada
}