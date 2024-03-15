#include "claves.h"
#include "mensaje.h"
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> // Necesario para la función wait()

int main() {
  int num_clients = 1; // Número de clientes a generar

  for (int i = 0; i < num_clients; i++) {
    pid_t pid = fork();

    if (pid == 0) {
      // Código del cliente
      int key = getpid() + i; // Usar un valor único para cada cliente
      char value1[20]; // Definir un array lo suficientemente grande para contener el PID convertido a cadena
      sprintf(value1, "%d", getpid()); // Convertir el PID a cadena y almacenarlo en value1
      int N_value2 = 3;
      double V_value2[] = {1.0, 2.0, 3.0};
      double V_value3[] = {1.0, 5.0, 159.0};


      // Ejecución diferente para cada cliente
      if (i == 0) {
        // Ejecución para el primer cliente
        printf("Cliente %d: Ejecución 1\n", getpid());
        init();
        set_value(key, value1, N_value2, V_value2);
        sleep(3); // Esperar un segundo para que el servidor termine de procesar la petición
        modify_value(key, value1, N_value2, V_value3);
        return 0; // Indicate successful execution
      }
    }
  }

  // Esperar a que todos los clientes terminen
  for (int i = 0; i < num_clients; i++) {
    wait(NULL);
  }

  return 0;
}