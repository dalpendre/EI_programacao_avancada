/**
 * @brief Código auxiliar de threads
 * @author Rui Ferreira
 * @version 1.0 
 */
 

//**********************************************************************
// 							criar uma (1) thread
//**********************************************************************

//  Protóptipos
void *task(void *arg);

// declaração global  ** (não copiar este comentário) ** 
// Estrutura a 'passar' às threads
typedef struct 
{
	int id;
}thread_params_t;



// na função main/outra  ** (não copiar este comentário) ** 
	pthread_t tid;
	thread_params_t thread_params;

	// Inicializa campos da estrutura a enviar à thread
	thread_params.id = 1;
		
	// cria uma thread + passagem de parâmetro
	if ((errno = pthread_create(&tid, NULL, task, &thread_params) != 0))
		ERROR(10, "Erro no pthread_create()!");
		
	
	// espera que a thread termine	
	if ((errno = pthread_join(tid, NULL)) != 0)
		ERROR(11, "Erro no pthread_join()!\n");
		


// Zona das funções  ** (não copiar este comentário) ** 
// Thread
void *task(void *arg) 
{
	// cast para o tipo de dados enviado pela 'main thread'
	thread_params_t *params = (thread_params_t *) arg;
	
	// para debug :: (apagar se não for necessário)
	printf("Teste: id = %d | TID = %lu\n", params->id, pthread_self());
	
	return NULL;
}






//**********************************************************************
// 							criar N Threads
//**********************************************************************

#define NUM_THREADS				        4

//  Protóptipos
void *task(void *arg);


// declaração global  ** (não copiar este comentário) ** 
// Estrutura a 'passar' às threads
typedef struct 
{
	int id;
}thread_params_t;


// na função main/outra  ** (não copiar este comentário) ** 
	pthread_t tids[NUM_THREADS];
    thread_params_t thread_params[NUM_THREADS];


	// Inicialização das estruturas - para cada thread
	for (int i = 0; i < NUM_THREADS; i++){
		thread_params[i].id = i + 1;

	}
	
	// Criação das threads + passagem de parâmetro
	for (int i = 0; i < NUM_THREADS; i++){
		if ((errno = pthread_create(&tids[i], NULL, task, &thread_params[i])) != 0)
			ERROR(10, "Erro no pthread_create()!");	
	}


    // Espera que todas as threads terminem
	for (int i = 0; i < NUM_THREADS; i++){
		if ((errno = pthread_join(tids[i], NULL)) != 0)
			ERROR(11, "Erro no pthread_join()!\n");
	}



// Zona das funções  ** (não copiar este comentário) ** 
// Thread
void *task(void *arg) 
{
	// cast para o tipo de dados enviado pela 'main thread'
	thread_params_t *params = (thread_params_t *) arg;
	
	// para debug :: (apagar se não for necessário)
	printf("Teste: id = %d | TID = %lu\n", params->id, pthread_self());
	
	return NULL;
}
