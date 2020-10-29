// includes
#include <stdio.h>

//**********************************************************************
// 					FICHEIROS - modo de acesso
//	r or rb - Open file for reading.
//	w or wb - Truncate to zero length or create file for writing.
//	a or ab - Append; open or create file for writing at end-of-file.
//	r+ or rb+ or r+b - Open file for update (reading and writing).
//	w+ or wb+ or w+b - Truncate to zero length or create file for update.
//	a+ or ab+ or a+b - Append; open or create file for update, writing at end-of-file
//**********************************************************************

// nota: usado no fgets()
#define MAX_LINE_CHARS				256


	// abrir o ficheiro "_FILE_" no modo "_MODE_"
	FILE *fp;
	if ((fp = fopen(_FILE_, "_MODE_")) == NULL)
		ERROR(5, "fopen() - não foi possível abrir o ficheiro");
		
	
	
	// ler a próxima linha do ficheiro (\n vem incluído na string)		
	char str_line[MAX_LINE_CHARS];
	if (fgets(str_line, MAX_LINE_CHARS, fp) == NULL)
		ERROR(7, "fgets() - não foi possível ler uma linha do ficheiro");	
		
		
		
				
	// fechar o ficheiro
	if (fclose(fp) != 0)
		ERROR(6, "fclose() - não foi possível fechar o ficheiro");
