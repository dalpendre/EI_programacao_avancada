//**********************************************************************
// 					tratamento de argumentos
//**********************************************************************
// _arg = valor do argumento
// _given = se o argumento foi ou não passado

#include "args.h"


	struct gengetopt_args_info args;

	// deve ser a primeira linha de código no main
	if( cmdline_parser(argc, argv, &args) ){
		ERROR(1, "Erro: execução de cmdline_parser\n");
	}


	// libertar recurso (assim que possível)
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

#option "flag" - "flag (estado inicial: off)" flag off
#option "argopcional" - "opção com argumento opcional" float argoptional default="3.14"

#option "multi" m "opção que pode ser especificadamais do que uma vez" optional multiple(1-3)
#option "multi2" - "opção múltipla até 4 vezes com parâmetro string" string optional multiple(1-4)

