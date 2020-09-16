/**
 * @brief  Código auxiliar de processos
 * @author Rui Ferreira
 * @version 1.0 
 */
 

// includes
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//**********************************************************************
// 					criação de um processo
//**********************************************************************
		
	pid_t pid;

	pid = fork();
	if (pid == 0) {			// Processo filho 
		printf("Filho \n");
		// processo_filho();		
		exit(0);			// Terminar processo filho
	} else if (pid > 0) {	// Processo pai 
		// usar preferencialmente a zona a seguir ao if
	} else					// < 0 - erro
		ERROR(2, "Erro na execucao do fork()");

	// Apenas processo pai
	printf("Pai \n");
	// processo_pai();
	
	// pai espera pelo filho
	wait(NULL);



//**********************************************************************
// 					criação de N processos
//**********************************************************************
#define NUM_PROCESSOS					3

	pid_t pid;
		
	// processo pai cria N processos
	for(int i = 0; i < NUM_PROCESSOS; i++){
		pid = fork();
		if (pid == 0) {			// Processo filho 
			printf("Filho %d \n", i + 1);
			
			exit(0);			// Termina processo filho (para este não criar novos processos)
		} else if (pid > 0) {	// Processo pai
			// usar preferencialmente a zona a seguir ao for
		} else					// < 0 - erro
			ERROR(2, "Erro na execucao do fork()");
	}
	
	// Apenas processo pai
	printf("Pai \n");
	
	// Espera pelos processos filhos
	for(int i = 0; i < NUM_PROCESSOS; i++){
		wait(NULL);
	}
	
	printf("Pai terminou \n");
	
