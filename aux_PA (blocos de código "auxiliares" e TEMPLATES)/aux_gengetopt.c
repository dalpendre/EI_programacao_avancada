/**
 * @brief Código auxiliar para uso do gengetopt
 * @author Rui Ferreira
 * @version 1.0 
 */
 

//**********************************************************************
// 					tratamento de argumentos
//**********************************************************************
// _arg = valor do argumento
// _given = se o argumento foi ou não passado

#include "args.h"


	struct gengetopt_args_info args;

	// gengetopt parser: deve ser a primeira linha de código no main
	if(cmdline_parser(argc, argv, &args))
		ERROR(1, "Erro: execução de cmdline_parser\n");



	// gengetopt: libertar recurso (assim que possível)
	cmdline_parser_free(&args);

	

	
	
// ********************   args.ggo    ******************************
// editar ficheiro: args.ggo
// executar: gengetopt < args.ggo
//# nota: retirado de "Revista Programar"::"A ferramenta gengetopt", por Patrício Domingues
//******************************************************************

package "Basic template"
version "1.0"
purpose "ei.pa"

# ---------- Argumentos da aplicação -------------------
option "exemplo" - "exemplo (opcional) com valor por omissão" string optional default="1.0"

//# ++++++++++++++++++++++++  Exemplos de definição das opções   +++++++++++++++++++++++++++++
#option "numero" n "requer numero inteiro(obrigatório)" int
#option "numero" n "requer numero inteiro(opcional)" long optional
#option "numero" n "requer numero inteiro(opcional) com valor por omissão" int optional default="0"

#option "enumerada" - "Uma opção cujo possíveis valores são especificados por values" values="zero","um","dois" default="zero" optional	

#option "obrigatoria" o "obrigatoria sem parâmetro"
#option "opcional" - "opcional sem parâmetro" optional
#option "argopcional" - "opção com argumento opcional" float argoptional default="3.14"



#option "flag" f "flag (estado inicial: off)" flag off
#
# exemplo da utilização na linha de comandos:
#	./prog -f on
#  ou
#	./prog --flag off
#
#
# exemplo da utilização na função main  (obtenção de informação disponível com esta opção)
#	printf("num = %d \n", args.flag_arg);




#option "multi" m "opção que pode ser especificadamais do que uma vez (1 até 3) (sem tipo de dados)" optional multiple(1-3)
#
# exemplo da utilização na linha de comandos:
#	./prog -m -m -m
#  ou
#	./prog --multi --multi
#
# exemplo da utilização na função main  (obtenção de informação disponível com esta opção)
#	printf("min = %d \n", args.multi_min);
#	printf("max = %d \n", args.multi_max);
#	printf("num = %d \n", args.multi_given);




#option "multi" m "opção múltipla até 4 vezes com parâmetro string" string optional multiple(1-4)
#
# exemplo da utilização na linha de comandos:
#	./prog -m a1 -m a2 -m a3	
#  ou
#	./prog -m a1,a2,a3	
#
# exemplo da utilização na função main (obtenção de informação disponível com esta opção)
#	printf("min = %d \n", args.multi_min);
#	printf("max = %d \n", args.multi_max);
#	printf("num = %d \n", args.multi_given);
#	for(int i = 0; i < args.multi_given; i++)
#		printf("val %d = %s \n", i, args.multi_arg[i]);

