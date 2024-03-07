#include CLAVES.H
#include mesnajes.h
#include <unistd.h>

int init() {
  mqd_t q_servidor;     	    /* cola de mensajes del servidor */
  mqd_t q_cliente;                /* cola de mensajes del cliente */
  struct peticion pet;      int res;      /* resultado de la operación */
  attr.mq_maxmsg = 10;
  //CREACION DE LA COLA DE MENSAJES,PONGO EL PID POR SI HAY VARIOS CLIENTES A LA VEZ
  char colalocal[]; // Definición de la variable local
  pid_t pid = getpid();    // Obtención del PID
  snprintf(colalocal, MAX_LEN, "COLA%d", (int)pid);    
	attr.mq_msgsize = sizeof(struct peticion);
        q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
	if (q_cliente == -1) {
		perror("mq_open");
		return -1;
  }
  q_servidor = mq_open("colaservidor.txt", O_WRONLY);
	if (q_servidor == -1){
		mq_close(q_cliente);
		perror("mq_open");
		return -1;
  }

  //RELLENAMOS EL MENSAJE
  pet.q_name = colalocal;
  pet.op = 0;
  //ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0){
		perror("mq_send");
		return -1;
	}	
  //RECIBIMOS EL MENSAJE
        if (mq_receive(q_cliente, (char *) &res, sizeof(int), 0) < 0){
		perror("mq_recv");
		return -1;
	}	
  //CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return 0;
  
  }

int set_value(int key, char *value1, int N_value2, double *V_value2){
  mqd_t q_servidor;     	    /* cola de mensajes del servidor */
  mqd_t q_cliente;                /* cola de mensajes del cliente */
  struct peticion pet;      int res;      /* resultado de la operación */
  attr.mq_maxmsg = 10;
  //CREACION DE LA COLA DE MENSAJES
  char colalocal[]; // Definición de la variable local
  pid_t pid = getpid();    // Obtención del PID
  snprintf(colalocal, MAX_LEN, "COLA%d", (int)pid);    
	attr.mq_msgsize = sizeof(struct peticion);
        q_cliente = mq_open(colalocal, O_CREAT|O_RDONLY, 0700, &attr);
	if (q_cliente == -1) {
		perror("mq_open");
		return -1;
  }
  q_servidor = mq_open("colaservidor.txt", O_WRONLY);
	if (q_servidor == -1){
		mq_close(q_cliente);
		perror("mq_open");
		return -1;
  }

  //RELLENAMOS EL MENSAJE
  pet.q_name = colalocal;
  pet.op = 0;
  pet.key=key;
  pet.value1=value1;//CREO QUE HAY FALLOS POR EL TEMA DE PUNETERO Y QUE NO SE PUEDE HACER ASI
  pet.N_value2=N_value2;
  pet.V_value2=V_value2;

  //ENVIAMOS EL MENSAJE
  if (mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0) < 0){
		perror("mq_send");
		return -1;
	}	
  //RECIBIMOS EL MENSAJE
        if (mq_receive(q_cliente, (char *) &res, sizeof(int), 0) < 0){
		perror("mq_recv");
		return -1;
	}	
  //CERRAMOS LAS COLAS
  mq_close(q_servidor);
  mq_close(q_cliente);
  mq_unlink(colalocal);
  return res.resultado;

  }

  
  

  


