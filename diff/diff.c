#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int diff(const char* archivo1, const char* archivo2){
	FILE* arch1 = fopen(archivo1, "r");
	if(arch1 == NULL){
		fprintf(stderr,"Archivo erroneo\n");
		return 1;
	}
	FILE* arch2 = fopen(archivo2, "r");
	if(arch2 == NULL){
		fprintf(stderr,"Archivo erroneo\n");
		fclose(arch1);
		return 1;
	}
	char *linea1 = NULL;
	char *linea2 = NULL;
	size_t tam1 = 0;
	size_t tam2 = 0;
	ssize_t letras1 = 1;
	ssize_t letras2 = 1;
	int linea = 1;
	letras1 = getline(&linea1,&tam1,arch1);
	letras2 = getline(&linea2,&tam2,arch2);
	while( letras1 != -1 && letras2 != -1 ){	
		if(strcmp(linea1,linea2) != 0){
			fprintf(stdout,"Diferencia en linea %d\n< %s---\n> %s", linea, linea1,linea2);
		}
		linea ++;
		letras1 = getline(&linea1,&tam1,arch1);
		letras2 = getline(&linea2,&tam2,arch2);
	}
	while(letras1 != -1){
		fprintf(stdout,"Diferencia en linea %d\n< %s---\n>\n", linea,linea1);
		linea++;
		letras1 = getline(&linea1,&tam1,arch1);
	}
	while(letras2 != -1){
		fprintf(stdout,"Diferencia en linea %d\n<\n---\n> %s", linea,linea2);
		linea++;
		letras2 = getline(&linea2,&tam2,arch2);
	}
	free(linea1);
	free(linea2);
	fclose(arch1);
	fclose(arch2);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr,"Cantidad de parametros erronea\n");
		return -1;
	}
	const char *archivo1 = argv[1];
	const char *archivo2 = argv[2];

	diff(archivo1, archivo2);
	return 0;
}