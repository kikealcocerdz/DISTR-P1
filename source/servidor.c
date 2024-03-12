#include "clavesservidor.h"
#include "mensaje.h"
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

mqd_t q_servidor;

void tratar_mensaje(struct peticion *mess) {
    int resultado; /* resultado de la operación */

    /* ejecutar la petición del cliente y preparar respuesta */
    switch (mess->op) {
        case 0:
            resultado = init_serv();
            break;
        case 1:
            resultado = set_value_serv(mess->key, mess->value1, mess->N_value2,
                                       mess->V_value2);
            break;
        case 2:
            resultado = get_value_serv(mess->key, mess->value1, mess->N_value2,
                                       mess->V_value2);
            break;
        case 3:
            resultado = modify_value_serv(mess->key, mess->value1, mess->N_value2,
                                          mess->V_value2);
            break;
        case 4:
            resultado = delete_value_serv(mess->key);
            break;
        default:
            resultado = exists_serv(mess->key);
            break;
    }

    /* Se devuelve el resultado al cliente */
    /* Para ello se envía el resultado a su cola */
    mqd_t q_cliente = mq_open(mess->q_name, O_WRONLY);
    if (q_cliente == -1) {
        perror("No se puede abrir la cola del cliente");
        mq_close(q_servidor);
        mq_unlink("/SERVIDOR_CLAVES");
        return;
    }

    if (mq_send(q_cliente, (const char *)&resultado, sizeof(int), 0) < 0) {
        perror("mq_send");
        mq_close(q_servidor);
        mq_unlink("/SERVIDOR_CLAVES");
        mq_close(q_cliente);
        return;
    }

    mq_close(q_cliente);
}

int main(void) {
    struct peticion mess;
    struct mq_attr attr;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct peticion);

    q_servidor = mq_open("/SERVIDOR_CLAVES", O_CREAT | O_RDONLY, 0700, &attr);
    if (q_servidor == -1) {
        perror("mq_open");
        return -1;
    }

    while (1) {
        if (mq_receive(q_servidor, (char *)&mess, sizeof(mess), 0) < 0) {
            perror("mq_receive");
            return -1;
        }

        tratar_mensaje(&mess);
    }

    return 0;
}
