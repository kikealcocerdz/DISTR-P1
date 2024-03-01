#include CLAVES.H

#include <unistd.h>

int init() {

  int init() {
    if (int fd = open("datos.dat", O_CREAT | O_RDWR | O_TRUNC, 0666) < 0) {
      perror("Error al abrir el archivo de datos");
      return -1;
    }
  }
}

int set_value(int key, char *value1, int N_value2, double *V_value_2) {
  struct mensaje mess;
  // Analizar los parametros y preparar el paquete
  mess.q_name = ip;
  mess.key = key;
}
