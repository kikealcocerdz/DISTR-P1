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
  int key2 = 2;
  char value2[] = "Hello Many Times";
  int N_value22 = 3;
  double V_value22[] = {1.0, 2.0, 3.0};
  delete_key(key2);
  exist(59);
  return 0;  // Indicate successful execution
}
