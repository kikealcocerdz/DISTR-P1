#define MAXSIZE 256
#ifndef MENSAJE_H
#define MENSAJE_H
// . . .

struct peticion {
  int op;               /* operación, 0 (+) 1 (-) */
  int key;              /* clave */
  char value1[MAXSIZE]; /* valor 1 */
  int N_value2;         /* dimensión del vector V_value2 [1-32] */
  char V_value2[32];  /* vector de doubles [32] */
  char q_name[MAXSIZE]; /* nombre de la cola de respuesta */
};

struct respuesta {
  int resultado; /* resultado de la operación ,es decir si ha salido bien o no (0 o -1)*/
  char value1[MAXSIZE]; /* valor 1 */
  int N_value2;         /* dimensión del vector V_value2 [1-32] */
  char V_value2[32];  /* vector de doubles [32] */
};

#endif // MENSAJE_H