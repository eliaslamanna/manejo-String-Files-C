#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "pila.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void apilar(pila_t* pila, char *linea, size_t i){
	if(pila_esta_vacia(pila)){
		if(linea[i] == ']' || linea[i] == ')' || linea[i] == '}'){
			pila_apilar(pila,&linea[i]);
		}
	}
	if(linea[i] == '[' || linea[i] == '(' || linea[i] == '{'){
		pila_apilar(pila,&linea[i]);
	}
}

void apilar_error(pila_t* pila, char* linea,char* tope, size_t i){
	char error = ']';
	if(linea[i] == ']' && *tope == '['){
		pila_desapilar(pila);
	}
	else if(linea[i] == ')' && *tope == '('){
		pila_desapilar(pila);
	}
	else if(linea[i] == '}' && *tope == '{'){
		pila_desapilar(pila);
	}
	else if(linea[i] == '}' || linea[i] == ')' || linea[i] == ']'){
		pila_apilar(pila, &error);
	}
}

void syntax_val(){
	char *linea = NULL;
	size_t tam = 0;
	ssize_t caracteres = 1;
	caracteres = getline(&linea,&tam,stdin);
	while(caracteres != -1){
		pila_t* pila = pila_crear();
		if(pila == NULL){
			return;
		}
		for(size_t i = 0; i < strlen(linea) - 1; i ++){
			if(linea[i] == '\''){
				pila_apilar(pila,&linea[i]);
				for(size_t j = i + 1; j < strlen(linea) - 1; j ++){
					if(linea[j] == '\''){
						pila_desapilar(pila);
						i = j;
						j = strlen(linea) - 1;
					}
				}
			}
			apilar(pila,linea,i);
			char *a;
			if(!pila_esta_vacia(pila)){
				a = pila_ver_tope(pila);
			}
			apilar_error(pila,linea,a,i);
		}
		if(!pila_esta_vacia(pila)){
			fprintf(stdout,"ERROR\n");
		}
		else{
			fprintf(stdout,"OK\n");
		}
		caracteres = getline(&linea,&tam,stdin);
		pila_destruir(pila);
	}
	free(linea);
}

int main(){
	syntax_val();
	return 0;
}