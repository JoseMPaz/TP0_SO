#include "client.h"

int main (void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	t_log * logger;
	t_config * config;
	char * ip, * puerto, *valor;
	int conexion;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	if (	config_has_property(config, "IP") &&
			config_has_property(config, "PUERTO") &&
			config_has_property(config, "LA_CLAVE") )
	{
		ip = config_get_string_value(config, "IP");
		puerto = config_get_string_value(config, "PUERTO");
		valor = config_get_string_value(config, "LA_CLAVE");
	}
	else
	{
		log_error(logger, "No se pudo leer el config");
		exit(EXIT_FAILURE);
	}

	//Muestra por consola los valores leídos del config
	printf("IP: %s\tPUERTO: %s\tLA_CLAVE: %s\n", ip, puerto, valor);

	// Loggeamos el "valor" de config
	log_info (logger, "CLAVE: %s\tVALOR: %s", "LA_CLAVE", valor);

	/* ---------------- LEER DE CONSOLA ---------------- */
	/*Lo leido lo almacena en logger */
	leer_consola (logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion (ip, puerto);
	log_info (logger, "Se conecto al servidor!");

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje (valor, conexion);
	printf ("%s%s\n", "Se envio el mensaje: ", valor);
	
	// Armamos y enviamos el paquete
	paquete(conexion);
	printf ("%s\n", "Se envio el paquete");
	
	terminar_programa (conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log * iniciar_logger (void)
{
	t_log * nuevo_logger = NULL;

	if ( (nuevo_logger = log_create ("tp0.log", "Cliente", true, LOG_LEVEL_INFO)) == NULL)
	{
		printf("No se pudo crear el logger\n");
		exit(EXIT_FAILURE);
	}

	return nuevo_logger;
}

t_config * iniciar_config (void)
{
	t_config * nuevo_config = NULL;

	if ( (nuevo_config = config_create ("./cliente.config")) == NULL)
	{
		printf("No se pudo leer el config\n");
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char * leido;
	
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	do
	{
		leido = readline("Ingresa un string (ENTER para salir): ");

		if (strcmp(leido, "") != 0)
		{
			log_info(logger, "Se ha ingresado el string: %s", leido);
			// ¡No te olvides de liberar las lineas antes de regresar!
			free(leido);
		}
	} while (strcmp(leido, "") != 0);
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);

	return;
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char * leido;
	t_paquete * paquete;
	
	paquete = crear_paquete ();
	// Leemos y esta vez agregamos las lineas al paquete
	do
	{
		leido = readline("String a empaquetar(ENTER para salir): ");

		if (strcmp(leido, "") != 0)
		{
			agregar_a_paquete (paquete, leido, strlen(leido) + 1);
			// ¡No te olvides de liberar las lineas antes de regresar!
			free(leido);
		}
	} while (strcmp(leido, "") != 0);
	
	enviar_paquete(paquete, conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  if (logger != NULL)
	  {
			log_destroy(logger);
	  }

	  if (config != NULL)
	  {
			config_destroy(config);
	  }
	  if (liberar_conexion (conexion) == -1) 
	  {
    	perror("close");
		}

	  return;
}
