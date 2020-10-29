#include <stdio.h>

int main(int argc, char *argv[])
{
	 (void)argc; (void)argv;

	int positive = 998;
	int negative = -998;
	int positive_shift, negative_shift;
	int i;
	
	for(i = 0; i < 4; i++){
		printf("===[shift right %d]===\n", i);
		positive_shift = positive >> i;
		negative_shift = negative >> i;
		printf("positive_shift = %d\n", positive_shift);
		printf("negative_shift = %d\n", negative_shift);
	}
	
	return 0;
}
