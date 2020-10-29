/**
 * @file memory.c
 * @brief Macros para gestão de memória
 *
 * Macros que serão usadas nos programas que requerem o uso das funções malloc e free
 * @version 1
 */
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

/**
 * Esta função deve ser utilizada para auxiliar a alocação de memória.
 * Esta função <b>não deve</b> ser chamada directamente, mas sim através
 * da macro MALLOC().
 * @param size tamanho do bloco a alocar
 * @param file nome do ficheiro
 * 	       (através da macro MALLOC)
 * @param line linha onde a função foi chamada
 * 	       (através da macro MALLOC)
 * @return O bloco de memória alocado
 * @see MALLOC
 */
void *eipa_malloc(size_t size, const int line, const char *file) {
	void *ptr = malloc(size);
	if( ptr == NULL ) {
		fprintf(stderr, "[%d@%s][ERROR] can't malloc %zu bytes\n",
			       	line, file, size);
	}
	return ptr;
}

/**
 * Esta função deve ser utilizada para auxiliar a libertação de memória.
 * Esta função <b>não deve</b> ser chamada directamente, mas sim através
 * da macro FREE().
 * @param ptr endereço do ponteiro a libertar
 * @param file nome do ficheiro
 * 	       (através da macro FREE)
 * @param line linha onde a função foi chamada
 * 	       (através da macro FREE)
 * @return A função não retorna nada
 * @see FREE
 */
void eipa_free(void **ptr, const int line, const char *file) {
	(void)line;
	(void)file;	
	free(*ptr);
	*ptr = NULL;
}
