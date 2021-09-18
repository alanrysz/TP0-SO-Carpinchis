/*
 * tp0.h
 *
 * Created on: 16 sep, 2021
 *	Author: utnso
 *
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include "utils.h"

#define PUERTO "PUERTO"
#define IP "IP"
#define VALOR "VALOR"

t_log* iniciar_logger(void);
t_config* leer_config(void);

void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* CLIENT_H_ */
