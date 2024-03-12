// cliente.c
#include "claves.h"
#include "mensaje.h"
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h> 

int main() {
  init();
  int key = 1;
  char value1[] = "Hello";
  int N_value2 = 3;
  double V_value2[] = {1.0, 2.0, 3.0};
  set_value(key, value1, N_value2, V_value2);
  return 0;  // Indicate successful execution
}

/*
gcc -c -fPIC claves.c -o claves.o
gcc -shared -o libclaves.so claves.o
gcc cliente.c libclaves.so -o cliente
./cliente
*/