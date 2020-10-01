#include "sorter.h"


/*
 * Sort string vector using inefficient bubble sort 
 * @param vector vector to sort
 * @param size number of elements in vector
 * @param criteria sort criteria
 */
void str_asort(const char *vector[], unsigned int size, STR_CMP criteria)
{
  int i, j;
  const char *temp;
  int test; /*use this only if unsure whether the list is already sorted or not*/
  for(i = size - 1; i > 0; i--)
  {
    test=0;
    for(j = 0; j < i; j++)
    {
      if(criteria(vector[j], vector[j+1]) > 0) /* compare neighboring elements using criteria */
      {
        temp = vector[j];    /* swap vector[j] and vector[j+1] */
        vector[j] = vector[j+1];
        vector[j+1] = temp;
        test=1;
      }
    } /*end for j*/
    if(test==0) break; /*will exit if the list is sorted!*/
  } /*end for i*/
}


