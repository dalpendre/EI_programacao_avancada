#ifndef SORTER_H
#define SORTER_H

typedef int (*STR_CMP)(const char *, const char *);

void str_asort(const char *vector[], unsigned int size, STR_CMP criteria); 

#endif
