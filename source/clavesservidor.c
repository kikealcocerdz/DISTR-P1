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
    FILE *claves = fopen("claves.txt", "w");
    if (claves == NULL) {
        perror("Error al abrir el archivo");
        return -1;  // Error al abrir el archivo
    }
    fclose(claves);
    // Truncate the file using the truncate system call
    if (truncate("claves.txt", 0) == -1) {
        perror("Error al truncar el archivo");
        return -1;  // Error al truncar el archivo
    }
    printf("Inicialización exitosa\n");
    return 0;  // Inicialización exitosa
}


int set_value_serv(int key, char *value1, int N_value2, double *V_value2) {
    FILE *clavesFile = fopen("claves.txt", "a");
    if (clavesFile == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Error al abrir el archivo
    }

    // Check if the key already exists
    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida == key) {
            fclose(clavesFile);
            return -1; // Clave encontrada, error ya que debe ser única
        }
    }

    // Move the file pointer to the end for appending
    fseek(clavesFile, 0, SEEK_END);

    // Insert the new key-value pair
    fprintf(clavesFile, "%d %s %d\n", key, value1, N_value2);

    fclose(clavesFile);
    printf("Clave insertada con éxito\n");
    return 0; // Inserción exitosa
}

int get_value_serv(int key, char *value1, int N_value2, double *V_value2)  {
    FILE *clavesFile = fopen("claves.txt", "r");
    if (clavesFile == NULL) {
        return -1; // Error al abrir el archivo
    }

    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida == key) {
            strcpy(value1, valor1);
            N_value2 = N_value2;
            // Assuming V_value2 is an array, copy it
            for (int i = 0; i < N_value2; i++) {
                fscanf(clavesFile, "%lf", &V_value2[i]);
            }
            fclose(clavesFile);
            printf("Clave leída con éxito: %s, %d, [", value1, N_value2);
            for (int i = 0; i < N_value2; i++) {
                printf("%lf ", V_value2[i]);
            }
            printf("]\n");
            return 0; // Lectura exitosa
        }
    }

    fclose(clavesFile);
    return -1; // Clave no encontrada
}


int modify_value_serv(int key, char *value1, int N_value2, double *V_value2) {
    FILE *clavesFile = fopen("claves.txt", "r+");
    if (clavesFile == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Error al abrir el archivo
    }

    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida == key) {
            // Calculate the length of the original line
            size_t originalLineLength = strlen(valor1) + strlen(value1) + 10; // Adjust as needed

            // Allocate memory for the entire line
            char *line = (char *)malloc(originalLineLength);

            // Read the entire line
            fseek(clavesFile, -originalLineLength, SEEK_CUR);
            fgets(line, originalLineLength, clavesFile);

            // Modify the value in memory
            sprintf(line, "%d %s %d", key, value1, N_value2);
            // Append the modified line to the end of the file
            fprintf(clavesFile, "%s", line);

            free(line);

            fclose(clavesFile);
            printf("Modificación exitosa\n");
            return 0; // Modificación exitosa
        }
    }

    fclose(clavesFile);
    return -1; // Clave no encontrada
}


#include <stdio.h>
#include <string.h>

int delete_value_serv(int key) {
    FILE *clavesFile = fopen("claves.txt", "r+");
    if (clavesFile == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Error al abrir el archivo
    }

    FILE *tempFile = tmpfile(); // Create a temporary file for rewriting

    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida != key) {
            fprintf(tempFile, "%d %s %d\n", key_leida, valor1, N_value2);
        }
    }

    // Rewind both files
    rewind(clavesFile);
    rewind(tempFile);

    // Copy contents from tempFile to clavesFile
    int c;
    while ((c = fgetc(tempFile)) != EOF) {
        fputc(c, clavesFile);
    }

    fclose(clavesFile);
    fclose(tempFile);

    printf("Eliminación exitosa\n");
    return 0; // Eliminación exitosa
}

#include <stdio.h>

int exists_serv(int key) {
    FILE *clavesFile = fopen("claves.txt", "r");
    if (clavesFile == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Error al abrir el archivo
    }

    while (fscanf(clavesFile, "%d %s %d", &key_leida, valor1, &N_value2) == 3) {
        if (key_leida == key) {
            fclose(clavesFile);
            printf("Clave encontrada\n");
            return 0; // Clave encontrada
        }
    }
    
    printf("Clave NO encontrada\n");
    fclose(clavesFile);
    return -1; // Clave no encontrada
}
