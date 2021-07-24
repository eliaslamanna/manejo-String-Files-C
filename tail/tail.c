#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "cola.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void tail(int n){
	size_t largo = 0;
	ssize_t letras;
	cola_t* cola = cola_crear();
	if(cola == NULL){
		return;
	}
	char *linea = NULL;
	int aux = 0;
	while(aux < n && getline(&linea,&largo,stdin) != -1){
		cola_encolar(cola,linea);
		linea = NULL;
		aux ++;
	}
	char *lineas = NULL;
	while((letras = getline(&lineas,&largo,stdin)) != -1){
		cola_encolar(cola,lineas);
		lineas = NULL;
		free(cola_desencolar(cola));
	}
	for(int i = 0; i < n; i ++){
		char *cadena = cola_desencolar(cola);
		if(cadena != NULL){
			fprintf(stdout,"%s", cadena);
		}
		free(cadena);
	}
	cola_destruir(cola,NULL);
	free(linea);
	free(lineas);
}

int main(int argc, char *argv[]){
	int numero = atoi(argv[1]);
	if(argc != 2){
		fprintf(stderr,"Cantidad de parametros erronea\n");
		return -1;
	}
	if(numero == 0){
		fprintf(stderr,"Tipo de parametro incorrecto\n");
		return -1;
	}
	tail(numero);
	return 0;
}