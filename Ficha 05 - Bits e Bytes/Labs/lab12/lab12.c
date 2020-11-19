#include <stdio.h>

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	unsigned int valor, valorA, valorB, valorC;

	// a) 0...01
	valor = 2 << 0;
	printf("[shift (2 << 0)]%u\n", valor);

	/*// b) 0...10	
	valor = 1 << 1;
	printf("[shift (1 << 1)]%u\n", valor);
	
	// c) 0...10101
	valor = 1 << 0 | 1 << 2 | 1 << 4;
	printf("[shift (1 << 0 | 1 << 2 | 1 << 4)]%u\n", valor);*/

	return 0;
}

