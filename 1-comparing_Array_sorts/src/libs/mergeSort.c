/*
 * implementation of mergeSort.h file
 */
// header files
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "swap.h"

/* function to merge array
 */
void merge(int rankArray[], int l, int m, int r) {
    // intialize variables
    int sub_arr1, sub_arr2, merged_arr;
    int node1 = m - l + 1;
    int node2 = r - m;
    
    // temp arrays
    int left[node1], right[node2];
    
    // copy data to temp arrays
    for (sub_arr1 = 0; sub_arr1 < node1; sub_arr1++)
        left[sub_arr1] = rankArray[l + sub_arr1];
    for (sub_arr2 = 0; sub_arr2 < node2; sub_arr2++)
        right[sub_arr2] = rankArray[m + 1 + sub_arr2];
    
    // merge temp arrays back into originial
    sub_arr1 = 0;
    sub_arr2 = 0;
    merged_arr = 0;
    while (sub_arr1 < node1 && sub_arr2 < node2) {
        if (left[sub_arr1] <= right[sub_arr2]) {
            rankArray[merged_arr] = left[sub_arr1];
            sub_arr1++;
        }
        else {
            rankArray[merged_arr] = right[sub_arr2];
            sub_arr2++;
        }
        merged_arr++;
    }
    // copy remaining elements of left node
    while (sub_arr1 < node1) {
        rankArray[merged_arr] = left[sub_arr1];
        sub_arr1++;
        merged_arr++;
    }
    while (sub_arr2 < node2) {
        rankArray[merged_arr] = right[sub_arr2];
        sub_arr2++;
        merged_arr++;
    }    
}

/*
 * Merge Sort Algorithm
 */
double runMergeSort(int rankArray[], unsigned long long int passwordArra[],
        int size) {
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();
    int l, m, r;

    if (l < r) {
        int m = l + (r - l) / 2;
        // sort first and second halves
        runMergeSort(rankArray, l, m);
        runMergeSort(rankArray, m + 1, r);
        merge(rankArray, l, m, r);
    }
    // end time
    endTime = clock();
    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    return totalTime;
}

