/*
 * implementation of insertionSort.h file
 */
// header files
#include <stdio.h>          // in/out
#include <time.h>           // measuring run time of our algos with this
#include <string.h>



/* 
 * Selection sort algorithm
 */
double runSelectionSort(int rankArray[], unsigned long long int passwordArray[],
                                                                    int size) {
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    unsigned long long int list, search, min, temp = 0;
    startTime = clock();

    // 1 by 1 move boundary of unsorted subarray
    for (list = 0; list < size - 1; list++) {
        min = list;


        for (search = list + 1; search < size; search++) {
            if (rankArray[search] < rankArray[min]) {
                min = search;
            }
        }
        // tempRank = swap(&rankArray[min], &rankArray[list]);
        temp = rankArray[min];
        rankArray[min] = rankArray[list];
        rankArray[list] = temp;

        temp = passwordArray[min];
        passwordArray[min] = passwordArray[list];
        passwordArray[list] = temp;

    }

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    return totalTime;
}

