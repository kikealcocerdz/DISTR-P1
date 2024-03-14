#include "claves.h"
#include "mensaje.h"
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 256
#define SUMA 0
#define RESTAR 1
#define MAX_LEN 20 // Add this line to define the size of 'colalocal'

int init() {

  printf("Inicialización empezada\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

	sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");

  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  pet.op = 0;
  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }

  printf("Mensaje enviado\n");
  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(int), 0) < 0) {
    perror("mq_recv");
    return -1;
  }
  printf("Mensaje recibido\n");

  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
}

int set_value(int key, char *value1, int N_value2, double *V_value2) {
  printf("SetValue empezado\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");

  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  pet.op = 1;
  pet.key = key;
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  strcpy(pet.value1, value1); // SE PUEDE HACER ASI
  pet.N_value2 = N_value2;
  memcpy(pet.V_value2, V_value2, sizeof(V_value2));
  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }
  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(int), 0) < 0) {
    perror("mq_recv");
    return -1;
  }
  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2) {
  printf("GetValue empezado\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

	sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");

  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  pet.op = 2;
  pet.key = key;
  strcpy(pet.value1, value1);
  pet.N_value2 = *N_value2;
  memcpy(pet.V_value2, V_value2, sizeof(V_value2));
  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }

  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
    perror("mq_recv");
    return -1;
  }

  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);

  // Devolvemos el respuesta de la operación
  return 0;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2) {
  printf("ModifyValue empezado\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

	sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");
  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  pet.op = 3;
  pet.key = key;
  strcpy(pet.value1, value1);
  pet.N_value2 = N_value2;
  memcpy(pet.V_value2, V_value2, sizeof(V_value2));
  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }
  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(int), 0) < 0) {
    perror("mq_recv");
    return -1;
  }
  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
}

int delete_key(int key) {
    printf("DeleteKey empezado\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

	sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");

  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  pet.op = 4;
  pet.key = key;

  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }
  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(int), 0) < 0) {
    perror("mq_recv");
    return -1;
  }
  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
}

int exist(int key) {
  printf("Exist empezado\n");
  mqd_t q_servidor; /* cola de mensajes del servidor */
  mqd_t q_cliente;  /* cola de mensajes del cliente */

  struct peticion pet;
  struct respuesta res; /* respuesta de la operación */
  struct mq_attr attr;  // Declare the 'attr' variable here
  char colalocal[MAXSIZE]; 

  // Initialize 'attr' before using it
  attr.mq_maxmsg = 10;     
	attr.mq_msgsize = sizeof(int);

  // CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A
  // LA VEZ

	sprintf(colalocal,  "/Cola-%d", getpid());
  q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
  if (q_cliente == -1) {
    perror("mq_open CLIENTE");
    return -1;
  }
  printf("Colas cliente creadas\n");

  q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_WRONLY, 0700, NULL);
  if (q_servidor == -1) {
    mq_close(q_cliente);
    perror("mq_open SERVIDOR");
    return -1;
  }
  printf("Cola servidor creadas\n");
  // RELLENAMOS EL MENSAJE
  strcpy(pet.q_name, colalocal);
  char claves[MAXSIZE];
  sprintf(claves, "%d.txt", getpid());
  strcpy(pet.claves, claves);
  pet.op = 5;
  pet.key = key;

  // ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0) {
    perror("mq_send");
    return -1;
  }
  // RECIBIMOS EL MENSAJE
  if (mq_receive(q_cliente, (char *)&res, sizeof(int), 0) < 0) {
    perror("mq_recv");
    return -1;
  }
  // CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
}