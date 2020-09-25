#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sorter.h"

void print_vector(const char **vector, unsigned int size);
int sort_by_length(const char *s1, const char *s2);
int sort_by_number_of_vogals(const char *s1, const char *s2);
unsigned int count_vogals(const char *s);

int main(int argc, char **argv)
{
	(void)argc;(void)argv; /* Silencia warnings */

	const char *vector_to_sort[13] = {
		"Human-Computer Interaction",
		"Software engineering I",
		"Databases",
		"Computer Networks",
		"Advanced Programming",
		"Internet Applications",
		"Software Engineering II",
		"Artificial Intelligence",
		"Database Systems",
		"Decision Support Systems",
		"Multimedia Systems",
		"Data Networks",
		"Management and Administration of Networks and Services"
	};	

	str_asort(vector_to_sort, 13, sort_by_length);
	printf("Order by length:\n");
	print_vector(vector_to_sort, 13);

	str_asort(vector_to_sort, 13, sort_by_number_of_vogals);
	printf("Order by number of vogals:\n");
	print_vector(vector_to_sort, 13);

	str_asort(vector_to_sort, 13, strcmp);
	printf("Alphabetic order:\n");
	print_vector(vector_to_sort, 13);

	exit(0);
}



int sort_by_length(const char *s1, const char *s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;
	return 0;
}

int sort_by_number_of_vogals(const char *s1, const char *s2) {
	int vogals1 = count_vogals(s1);
	int vogals2 = count_vogals(s2);
	if (vogals1 > vogals2)
		return 1;
	if (vogals1 < vogals2)
		return -1;
	return 0;
}

unsigned int count_vogals(const char *s) {
	unsigned int  i, total = 0;
	for (i = 0; i < strlen(s); i++)
		switch(tolower(s[i])) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				total++;
		}
	return total;
}

void print_vector(const char **vector, unsigned int size) {
	unsigned i;
	for (i=0; i < size; i++)
		printf("\t%s\n", vector[i]);
	printf("\n");
}



