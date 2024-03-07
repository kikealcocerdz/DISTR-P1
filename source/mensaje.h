#define MAXSIZE 256
#define SUMA 0
#define RESTAR 1
// . . .

struct peticion {
  int op;               /* operación, 0 (+) 1 (-) */
  int key;              /* clave */
  char value1[MAXSIZE]; /* valor 1 */
  int N_value2;         /* dimensión del vector V_value2 [1-32] */
  double V_value2[32];  /* vector de doubles [32] */
  char q_name[MAXSIZE]; /* nombre de la cola de respuesta */
  int resultado;        /* resultado de la operación ,esdecir si ha salido bien o no (0 o -1)*/
};