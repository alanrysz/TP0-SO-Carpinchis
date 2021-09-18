#include "tp0.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

const char *CONFIG_FIELDS[] = { IP, PUERTO, VALOR };

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;


	t_log* logger;
	t_config* config;

	/* ----------LOGING ------------*/

	logger = iniciar_logger();

	//Usando el lolgger creado previamente
	//Escribi "Hola! Soy un log"

	log_info(logger, "Hola soy un log");

	/*---------ARCHIVOS DE CONFIGURACION --------*/

	config = leer_config();

	//Usando el config creado previamente, leemos los valores del config y los
	//dejamos en las variables 'ip', puerto y valor

	ip = config_get_string_value(config, IP);
	puerto = config_get_string_value(config,PUERTO);
	valor = config_get_string_value(config, VALOR);

	//loggeamos el valor de las config
	log_info(logger,"IP: %s",ip);
	log_info(logger,"PUERTO: %s" ,puerto);
	log_info(logger,"VALOR: %s" ,valor);

	/*-----------Leer de consola---------*/

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE (valor) al servirdor
	enviar_mensaje(valor,conexion);

	//Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	if((nuevo_logger = log_create("tp0.log", "Client", 1, LOG_LEVEL_INFO)) == NULL){
		printf("No pude crear el log\n");
		exit(1);

	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

t_config* leer_config(void){

	t_config* nuevo_config;

	if ((nuevo_config = config_create("tp0.config")) == NULL){
		printf("No se puede leer el archivo de config\n");
		exit(2);
		}
}

void leer_consola(t_log* logger){


	char* buffer = "";
	buffer = readline("Ingresar una palabra: ");
	char* vacio="";

	while(strcmp(vacio,buffer)!=0){

		log_info(logger,buffer);
		buffer = readline("Ingresar una palabra: ");
	}

	free(buffer);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete_mandar =crear_paquete();

	while(strcmp(leido = readline("Ingrese para mandar al servidor: "), "")){
		agregar_a_paquete(paquete_mandar, leido, (strlen(leido+1)));
		//free(leido);
	}
	enviar_paquete(paquete_mandar, conexion);
	eliminar_paquete(paquete_mandar);
	free(leido);


}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	if (logger != NULL)
		log_destroy(logger);
	if(config != NULL)
		config_destroy(config);

	liberar_conexion(conexion);

}
