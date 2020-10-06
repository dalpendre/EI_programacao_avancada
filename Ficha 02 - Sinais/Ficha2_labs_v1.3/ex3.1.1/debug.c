/* <%LICENSE%> */
/**
 * @file debug.c
 * @brief Funções de depuração
 *
 * Funções de depuração que serão chamadas através das respectivas
 * macros definidas no ficheiro debug.h. O objectivo destas funções 
 * é auxiliar o tratamento de erros e a depuração
 *
 * @todo revisão do código
 * 
 * @author Miguel Frade, Patricio Domingues, Vitor Carreira
 * @date Agosto de 2003
 * @version 2 
 * @par Diferenças da última versão
 * Actualização dos comentários doxygen.
 * As funções error e h_error passaram a incluir "exitCode"
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#include "debug.h"

/**
 * Esta função deve ser utilizada para auxiliar a depuração de programas.
 * Esta função <b>não deve</b> ser chamada directamente, mas sim através
 * da macro DEBUG().
 *
 * @param file nome do ficheiro
 * 	       (através da macro DEBUG)
 * @param line linha onde a função foi chamada
 * 	       (através da macro DEBUG)
 * @param fmt string de formatação como no "printf"
 * @param ... nº variável de parâmetros
 * @return A função não retorna nada
 * @see DEBUG
 */
void debug(const char *file, const int line, char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "[%s@%d] DEBUG - ", file, line);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    fflush(stderr);
}


/**
 * Função que envia para o canal de erros a mensagem "WARNING" rotulada
 * com o nome do ficheiro e da linha da função chamante e ainda da mensagem de
 * erro do sistema. A função <b>não deve</b> ser chamada directamente, mas sim
 * através da macro WARNING().
 *
 * @param file nome do ficheiro fonte da função chamante
 * 	       (através da macro WARNING)
 * @param line linha onde a função foi chamada
 * 	       (através da macro WARNING)
 * @param fmt string de formatação como no "printf"
 * @param ... nº variável de parâmetros
 * @return A função não retorna nada
 * @see WARNING
 */
void warning(const char *file, const int line, char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "[%s@%d] WARNING - ", file, line);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", strerror(errno));
    fflush(stderr);
}



/**
 * Função que envia para o canal de erros a mensagem "ERROR" rotulada
 * com o nome do ficheiro e da linha da função chamante, e ainda da mensagem de
 * erro do sistema. A função <b>não deve</b> ser chamada directamente, mas sim
 * através da macro ERROR().
 *
 * @param file nome do ficheiro fonte da função chamante
 * 	       (através da macro ERROR)
 * @param line linha onde a função foi chamada
 * 	       (através da macro ERROR)
 * @param exitCode valor passado à função "exit()"
 * @param fmt string de formatação como no "printf"
 * @param ... nº variável de parâmetros
 * @return A função não retorna nada
 * @see ERROR
 */
void error(const char *file, const int line, int exitCode, char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "[%s@%d] ERROR - ", file, line);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", strerror(errno));
    fflush(stderr);
    exit(exitCode);
}


/**
 * Função que envia para o canal de erros a mensagem "H_WARNING" rotulada
 * com o nome do ficheiro e da linha da função chamante, e ainda da mensagem de
 * erro do sistema. A função <b>não deve</b> ser chamada directamente, mas sim
 * através da macro H_WARNING().
 *
 * @param file nome do ficheiro fonte da função chamante
 * 	       (através da macro H_WARNING)
 * @param line linha onde a função foi chamada
 * 	       (através da macro H_WARNING)
 * @param fmt string de formatação como no "printf"
 * @param ... nº variável de parâmetros
 * @return A função não retorna nada
 * @see H_WARNING
 */
void h_warning(const char *file, const int line, char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "[%s@%d] H_WARNING - ", file, line);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", hstrerror(h_errno));
    fflush(stderr);
}


/**
 * Função que envia para o canal de erros a mensagem "H_ERROR" rotulada
 * com o nome do ficheiro e da linha da função chamante, e ainda da mensagem de
 * erro do sistema. A função <b>não deve</b> ser chamada directamente, mas sim
 * através da macro H_ERROR().
 *
 * @param file nome do ficheiro fonte da função chamante 
 * 	       (através da macro H_ERROR)
 * @param line linha onde a função foi chamada
 * 	       (através da macro H_ERROR)
 * @param exitCode valor passado à função "exit()"
 * @param fmt string de formatação como no "printf"
 * @param ... nº variável de parâmetros
 * @return A função não retorna nada
 * @see H_ERROR
 */
void h_error(const char *file, const int line, int exitCode, char *fmt,
	     ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "[%s@%d] H_ERROR - ", file, line);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", hstrerror(h_errno));
    fflush(stderr);
    exit(exitCode);
}
