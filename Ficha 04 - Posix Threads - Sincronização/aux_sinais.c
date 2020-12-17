/**
 * @brief Código auxiliar de sinais
 * @author Rui Ferreira
 * @version 1.0 
 */
 

// includes
#include <signal.h>

//**********************************************************************
// 							SINAIS (sem info) 
//**********************************************************************

// zona dos protótipos
void trata_sinal(int signal);


// zona das funções
void trata_sinal(int signal)
{
	int aux;	
	aux = errno;   // Copia da variável global errno 
	
	// código
	printf("Recebi o sinal (%d)\n", signal);		
	
	errno = aux;   // Restaura valor da variável global errno
}

// início da main/função
	struct sigaction act;
		
		
// algures... no local mais adequado		
	act.sa_handler = trata_sinal; 	// Definir a rotina de resposta a sinais 
	sigemptyset(&act.sa_mask);  	// mascara sem sinais -- nao bloqueia os sinais 
	act.sa_flags = 0;           	
	//act.sa_flags |= SA_RESTART; 	// recupera chamadas bloqueantes

	// Captura do sinal ??? 
	if(sigaction(???, &act, NULL) < 0)
		ERROR(3, "sigaction (sa_handler) - ???");




//**********************************************************************
// 							SINAIS (com info) 
//**********************************************************************
// zona dos protótipos
void trata_sinal_info(int signal, siginfo_t *siginfo, void *context);


// zona das funções
void trata_sinal_info(int signal, siginfo_t *siginfo, void *context) 
{
	(void)context;
	/* Cópia da variável global errno */
	aux = errno;


	printf("Recebi o sinal (%d)\n", signal);
	printf("Detalhes:\n");
	printf("\tPID: %ld\n\tUID: %ld\n", (long)siginfo->si_pid, (long)siginfo->si_uid);


	/* Restaura valor da variável global errno */
	errno = aux;
}


// início da main/função
	struct sigaction act_info;
		
// algures... no local mais adequado
	act_info.sa_sigaction = trata_sinal_info;
	sigemptyset(&act_info.sa_mask);
	act_info.sa_flags = 0;           	//fidedigno
	act_info.sa_flags |= SA_SIGINFO; 	//info adicional sobre o sinal
	//act_info.sa_flags |= SA_RESTART; 	//recupera chamadas bloqueantes

// Captura do sinal ??? 
	if(sigaction(SIGUSR1, &act_info, NULL) < 0)
		ERROR(4, "sigaction (sa_sigaction) - ???");

	
	
	
	
