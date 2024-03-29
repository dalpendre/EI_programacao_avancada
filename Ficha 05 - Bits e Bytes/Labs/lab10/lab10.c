#include <stdio.h>

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	short A = 0x1122;
	short C = A ^ (~A);		/* applies binary XOR to itself */

	printf("A = 0x%hx, A xor (~A) => 0x%hx\n", A, C);
	printf("A xor (~A) => %hd (decimal)\n", C);
	printf("size_of_short = %ld\n", sizeof(short) * 8);

	return 0;
}
