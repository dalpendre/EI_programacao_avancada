
//**********************************************************************
// 							contabilizar tempo
//**********************************************************************
// includes 
#include <sys/time.h>

    struct timeval tv_begin, tv_end;

	// iniciar cronómetro
	gettimeofday(&tv_begin, NULL);
	
// tarefa a cronometrar...	
	
	// parar cronómetro
	gettimeofday(&tv_end, NULL);
	
    // Mostrar informação sobre o tempo realizador
    printf("seconds: %ld | milliseconds %03ld \n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec) / 1000);
    printf("milliseconds %ld \n", (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec - tv_begin.tv_usec) / 1000);
	
	
//**********************************************************************
// 							números aleatóreos
//**********************************************************************	

//	início do da função/main
	srandom(time(NULL)*getpid());
	
//	obter número aleatóreo (0 até N-1)
	random() % 10;		// 0 até 9
