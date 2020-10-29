#include <stdio.h>

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	unsigned int valor = 1;
	unsigned int valor_shift;
	size_t size_bits = sizeof(valor) * 8;
	unsigned int i;
	
	for(i = 0; i < size_bits; i++){
		valor_shift = valor << i;
		printf("[shift (valor << %02u)]%u\n", i, valor_shift);
	}

	return 0;
}

