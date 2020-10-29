#include <stdio.h>

int main(int argc, char *argv[])
{
	 (void)argc; (void)argv;

	 short A = 0x1122;
	 short B = 0x2211;
	 short C = A & B;	/* applies binary AND */

	 printf("A = 0x%hx, B = 0x%hx, C = 0x%hx\n", A, B, C);
	 printf("size_of_short = %d\n", sizeof(short) * 8);

	 return 0;
}