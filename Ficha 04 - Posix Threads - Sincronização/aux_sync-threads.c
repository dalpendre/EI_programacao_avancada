/**
 * @brief Código auxiliar de sincronização de threads
 * @author Rui Ferreira
 * @version 1.0 
 */ 


//**********************************************************************
// 							MUTEXs
//**********************************************************************

//----------------------------------------
// declarar na estrutra 'thread_params_t' o campo: 
	pthread_mutex_t *ptr_mutex;

// +++++++ (main)  +++++++

	pthread_mutex_t mutex;
	thread_params.ptr_mutex = &mutex;
	
	// Mutex: inicializa o mutex antes de criar a(s) thread(s)	
	if ((errno = pthread_mutex_init(&mutex, NULL)) != 0)
		ERROR(12, "pthread_mutex_init() failed");


	// Mutex: liberta recurso
	if ((errno = pthread_mutex_destroy(&mutex)) != 0)
		ERROR(13, "pthread_mutex_destroy() failed");
		

//----------------------------------------
// +++++++ (threads) +++++++
	
	// Mutex: entra na secção crítica 
	if ((errno = pthread_mutex_lock(params->ptr_mutex)) != 0){		
		WARNING("pthread_mutex_lock() failed");
		return NULL;
	}
	
	//  #######   Secção crítica   ######
	
	// Mutex: sai da secção crítica 
	if ((errno = pthread_mutex_unlock(params->ptr_mutex)) != 0){
		WARNING("pthread_mutex_unlock() failed");
		return NULL;
	}





//**********************************************************************
// 					VARIÁVEIS DE CONDIÇÃO
//**********************************************************************

//----------------------------------------
// declarar na estrutra 'thread_params_t' o campo: 
	pthread_cond_t *ptr_cond;

// +++++++ (main)  +++++++
	pthread_cond_t cond;
	thread_params.ptr_cond = &cond;

	// Var.Condição: inicializa variável de condição
	if ((errno = pthread_cond_init(&cond, NULL)) != 0)
		ERROR(14, "pthread_cond_init() failed!");
	
	
	// Var.Condição: destroi a variável de condição 
	if ((errno = pthread_cond_destroy(&cond)) != 0)
		ERROR(15,"pthread_cond_destroy failed!");



//----------------------------------------
// +++++++ (threads) +++++++

	// Var.Condição: bloqueia a thread usando a variável de condição (em conjunto com o mutex)
	while (???){		
		if ((errno = pthread_cond_wait(params->ptr_cond, params->ptr_mutex)!=0)){   
			WARNING("pthread_cond_wait() failed");
			return NULL;
		}
	}



	// Var.Condição: notifica a primeira thread à espera na variável de condição
	if ((errno = pthread_cond_signal(params->ptr_cond)) != 0){
		WARNING("pthread_cond_signal() failed");
		return NULL;
	}

// ou

	// Var.Condição: notifica TODAS as threads à espera na variável de condição
	if ((errno = pthread_cond_broadcast(params->ptr_cond)) != 0){
		WARNING("pthread_cond_broadcast() failed");
		return NULL;
	}
