/*
 * implementation of bubbleSort.h file
 */
// header files
#include <stdio.h>          // in/out
#include <time.h>           // measuring run time of our algos with this
#include <string.h>

/*
Name: runBubbleSort
Process: sorts data with bubble sort algorithm
Function input/parameters: array for rank, array for password,
                                 and size (number to be sorted)
Function output/parameters: sorted arrays
Function output/returned: length of time of sort (provided)
Device input/file: none
Device output/monitor: none
Dependencies: clock, compareData, swap
*/

double runBubbleSort(int rankArray[], unsigned long long int passwordArray[],
                                                                    int size) {
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    int list, search, swap = 0;

    startTime = clock();

    // outer loop: n-1 elements
    for (list = 0; list < (size - 1); list++) {
        // inner loop: n-1 elements
        for (search = 0; search < size - list - 1; search++) {
            // check to see if next element is larger than current
            if (rankArray[search] > rankArray[search + 1]) {
                // swap current and next element 
                swap = rankArray[search];
                rankArray[search] = rankArray[search + 1];
                rankArray[search + 1] = swap;

                swap = passwordArray[search];
                passwordArray[search] = passwordArray[search + 1];
                passwordArray[search + 1] = swap;
            }
        }
    }

    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;
}


