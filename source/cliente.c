#include "claves.h"
#include "mensaje.h"
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h> // Necesario para la función wait()

int main() {
  int num_clients = 3; // Número de clientes a generar

  for (int i = 0; i < num_clients; i++) {
    pid_t pid = fork();

    if (pid == 0) {
      // Código del cliente
      int key = getpid() + i; // Usar un valor único para cada cliente
      char value1[20]; // Definir un array lo suficientemente grande para contener el PID convertido a cadena
      sprintf(value1, "%d", getpid()); // Convertir el PID a cadena y almacenarlo en value1
      int N_value2 = 3;
      double V_value2[] = {1.0, 2.0, 3.0};

      // Ejecución diferente para cada cliente
      if (i == 0) {
        // Ejecución para el primer cliente
        printf("Cliente %d: Ejecución 1\n", getpid());
        set_value(key, value1, N_value2, V_value2);
        delete_key(key);
      } else if (i == 1) {
        // Ejecución para el segundo cliente
        printf("Cliente %d: Ejecución 2\n", getpid());
        // Agregar una clave con diferente valor
        N_value2 = 2;
        double V_value2[] = {4.0, 5.0};
        set_value(key, value1, N_value2, V_value2);
      } else {
        // Ejecución para el tercer cliente
        printf("Cliente %d: Ejecución 3\n", getpid());
        // Agregar una clave con diferente valor
        N_value2 = 1;
        double V_value2[] = {6.0};
        set_value(key, value1, N_value2, V_value2);
      }

      // Esperar un momento antes de borrar la clave
      sleep(1);

      // Borrar la clave agregada
      delete_key(key);

      exist(59);
      return 0; // Indicate successful execution
    }
  }

  // Esperar a que todos los clientes terminen
  for (int i = 0; i < num_clients; i++) {
    wait(NULL);
  }

  return 0;
}
