/*
 *  header file for merge sort function defs
 */

#ifndef MERGESORT_H
#define MERGESORT_H
// header files
//#include "consts.h"

void merge(int rankArray[], unsigned long long int passwordArray[], int size, 
        int l, int m, int r);

double runMergeSort(int rankArray[], unsigned long long int passwordArray[], 
        int size, int l, int r);

#endif

