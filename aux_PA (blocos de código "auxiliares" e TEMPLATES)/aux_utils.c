/**
 * @brief Código auxiliar - utils
 * @author Rui Ferreira
 * @version 1.1 
 */
 

//**********************************************************************
// 					contabilizar tempo
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
//					esperar milisegundos
//**********************************************************************	
// includes 
#include <time.h>

	// definição do tempo (ms) a esperar	
	struct timespec delay_ms = {0};
	delay_ms.tv_sec = (???segundos[>= 0])???);
	delay_ms.tv_nsec = 1000000 * (???milisegundos[0-999])???);	
	
	// esperar
	nanosleep(&delay_ms, NULL);
	
	
//**********************************************************************
// 					números aleatóreos
//**********************************************************************	
//  antes dos includes
#define _DEFAULT_SOURCE

//	início do da função/main
	srandom(time(NULL)*getpid());
	
//	obter número aleatóreo (0 até N-1)
	random() % 10;		// 0 até 9



//**********************************************************************
//			obter informação sobre o utilizador atual
//**********************************************************************	
#include <sys/types.h>
#include <pwd.h>

/* informação sobre a estrutura
The passwd structure is defined in <pwd.h> as follows:
struct passwd {
   char   *pw_name;       /* username */
   char   *pw_passwd;     /* user password */
   uid_t   pw_uid;        /* user ID */
   gid_t   pw_gid;        /* group ID */
   char   *pw_gecos;      /* user information */
   char   *pw_dir;        /* home directory */
   char   *pw_shell;      /* shell program */
};
*/

// no código....
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw){
		printf("%s\n", pw->pw_name);
	}

