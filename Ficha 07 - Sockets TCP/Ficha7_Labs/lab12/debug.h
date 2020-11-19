/* <%LICENSE%> */
/**
 * @file debug.h
 * @brief Macros das funções de depuração
 *
 * Macros que serão usadas nos programas desenvolvidos ao longo
 * do livro. Estas macros podem receber um número variável de parâmetros
 * através de uma string de formatação como no "printf". Seguem-se alguns 
 * exemplos: 
 * @code
 * DEBUG("i = %d e f=.2f%", i, f);
 * ERROR("%s", msg);
 * @endcode
 * @author Miguel Frade, Patricio Domingues, Vitor Carreira
 * @date Agosto de 2003
 * @version 2
 * @par Diferenças da última versão
 * Actualização dos comentários doxygen
 * Inclusão do "exitCode" nas macros ERROR e H_ERROR
 */
#ifndef DEBUG_H
#define DEBUG_H

void debug(const char *file, const int line, char *fmt, ...);
void warning(const char *file, const int line, char *fmt, ...);
void error(const char *file, const int line, int exitCode, char *fmt, ...);
void h_warning(const char *file, const int line, char *fmt, ...);
void h_error(const char *file, const int line, int exitCode, char *fmt,
	     ...);


/**
 * Macro para imprimir no stderr informações úteis 
 * para depuração. O número de parâmetros de entrada
 * é variável.
 * 
 * @return A função não retorna nada
 * @see debug()
 */
#define DEBUG(...) debug(__FILE__, __LINE__, __VA_ARGS__)


/**
 * Macro para imprimir no stderr informação relacionada
 * com insucesso de chamadas de funções, mas não termina a
 * execução do programa. O número de parâmetros de entrada
 * é variável.
 *
 * @return A função não retorna nada
 * @see warning()
 */
#define WARNING(...) warning(__FILE__, __LINE__, __VA_ARGS__)


/**
 * Macro para imprimir no stderr informação relacionada
 * com insucesso de chamadas de funções e termina a execução
 * do programa. O número de parâmetros de entrada é variável.
 *
 * @return A função não retorna nada
 * @see error()
 */
#define ERROR(exitCode, ...) \
	error(__FILE__, __LINE__, (exitCode), __VA_ARGS__)


/**
 * Macro para imprimir no stderr informação relacionada
 * com insucesso de chamadas de funções de resolução de nomes,
 * mas não termina a execução do programa. O número de 
 * parâmetros de entrada é variável.
 *
 * @return A função não retorna nada
 * @see h_warning()
 */
#define H_WARNING(...) h_warning(__FILE__, __LINE__, __VA_ARGS__)


/**
 * Macro para imprimir no stderr informação relacionada
 * com insucesso de chamadas de funções de resolução de nomes 
 * e termina a execução do programa. O número de parâmetros
 * de entrada é variável.
 *
 * @return A função não retorna nada
 * @see h_error()
 */
#define H_ERROR(exitCode, ...) \
	h_error(__FILE__, __LINE__, (exitCode), __VA_ARGS__)


#endif				/* DEBUG_H */
