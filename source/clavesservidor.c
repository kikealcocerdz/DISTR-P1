#include <stdio.h>
#include "clavesservidor.h"
#include <mqueue.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

int claves;
int key_leida;
char valor1[100];
int N_value2;
double V_value2[100];
struct respuesta res; 

void init_serv(struct respuesta *res) {
    // Eliminar el directorio /claves si existe
    if (access("./claves", F_OK) == 0) {
        DIR *dir = opendir("./claves");
        if (dir) {
            // Si el directorio está lleno, elimina su contenido
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    char path[1024];
                    snprintf(path, sizeof(path), "%s/%s", "./claves", entry->d_name);
                    remove(path);
                }
            }
            closedir(dir);
        }
        // Eliminar el directorio /claves
        if (remove("./claves") == -1) {
            res->resultado = -1;
            return;  // Error al eliminar el directorio
        }
    }
    // Crear el directorio /claves
    if (mkdir("./claves", 0777) == -1) {
        res->resultado = -1;
        return;   // Error al crear el directorio
    }

    printf("Inicialización exitosa\n");
    res->resultado = 0;
    return;  // Error al eliminar el directorio // Inicialización exitosa
}

void set_value_serv(int key, char *value1, int N_value2, char *V_value2, struct respuesta *res) {
    char filename[20]; // Tamaño suficiente para almacenar el valor de la clave como una cadena
    sprintf(filename, "./claves/%d.txt", key); // Convertir la clave en una cadena y añadir el directorio
    FILE *checkExistFile = fopen(filename, "r");
    if (checkExistFile != NULL) {
        fclose(checkExistFile);
        res->resultado = -1;
        return;
    }
    
    FILE *clavesFile = fopen(filename, "w+");
    if (clavesFile == NULL) {
        perror("Error al abrir el archivo");
        res->resultado = -1;
        return;
    }

    // Insertar la nueva clave-valor
    fprintf(clavesFile, "%d %s %d %s", key, value1, N_value2, V_value2); // Agregar la clave, valor1, y V_value2 al archivo
    fprintf(clavesFile, "\n"); // Nueva línea al final
    fclose(clavesFile);
    res->resultado = 0;
    return;
}

void get_value_serv(int key, char *value1, int *N_value2, char *V_value2, struct respuesta *res) {
    char filename[20]; // Tamaño suficiente para almacenar el valor de la clave como una cadena
    sprintf(filename, "./claves/%d.txt", key); // Convertir la clave en una cadena y añadir el directorio
    FILE *clavesFile = fopen(filename, "r");
    if (clavesFile == NULL) {
        res->resultado = -1;
        return;
    }

    // Leer el contenido del archivo y almacenarlo en las variables
    if (fscanf(clavesFile, "%d %s %d %s", &key, value1, N_value2, V_value2) != 4) {
        fclose(clavesFile);
        res->resultado = -1;
        return;
    }

    // Cerrar el archivo
    fclose(clavesFile);
    res->resultado = 0;
    strcpy(res->value1, value1);
    res->N_value2 = *N_value2;
    strcpy(res->V_value2, V_value2);
    return;
}

void delete_value_serv(int key, struct respuesta *res) {
    char filename[20]; // Tamaño suficiente para almacenar el valor de la clave como una cadena
    sprintf(filename, "./claves/%d.txt", key); // Convertir la clave en una cadena y añadir el directorio

    // Verificar si el archivo existe
    if (access(filename, F_OK) != 0) {
        res->resultado = -1;
        return;
    }

    // Eliminar el archivo
    if (unlink(filename) == -1) {
        res->resultado = -1;
        return;
    }

    res->resultado = 0;
    return;
}

void modify_value_serv(int key, char *value1, int N_value2, char *V_value2, struct respuesta *res) {
    // Eliminar el archivo correspondiente a la clave dada
    printf("V_value2: %s\n", V_value2);
    delete_value_serv(key, res);
    printf("V_value2: %s\n", V_value2);
    // Llamar a set_value_serv para crear un nuevo archivo con el nuevo valor
    set_value_serv(key, value1, N_value2, V_value2, res);
    res->resultado = 0;
    res->N_value2 = N_value2;
    return;
}

void exists_serv(int key, struct respuesta *res) {
    char filename[20]; // Tamaño suficiente para almacenar el valor de la clave como una cadena
    sprintf(filename, "./claves/%d.txt", key); // Convertir la clave en una cadena y añadir el directorio

    FILE *clavesFile = fopen(filename, "r");
    if (clavesFile == NULL) {
        res->resultado = 0;
        return;
    }
    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida == key) {
            fclose(clavesFile);
            printf("Clave encontrada\n");
            res->resultado = 1;
            return;
        }
    }
    
    fclose(clavesFile);
    res->resultado = -1;
    return;
}
