/*  C Program displaying knowledge of different sorting algorithms.
 *  Goal is to read in csv file of unsorted data (300,000 data pairs)
 *  containing a key and a value. In this case password rank and its 
 *  corresponding password. We are to sort the rankArray of ints
 *  and assign the iterated positions to passwordArray of 
 *  unsigned long long ints. Using bubble and insertion sort we sort the
 *  values and export them into files of their respective names.
 *  
 *  Author: Akiel Aries
 */


// header files
#include <stdio.h>              // file io
#include <time.h>               // measuring time
#include <string.h>             
#include "bubbleSort.h"         // bubble sort algorithm
#include "insertionSort.h"      // insertion sort algorithm
#include "selectionSort.h"      // selection sort algorithm

// global constants
const int MAX_CAPACITY = 150001;

// main driver
int main() {
    // initialize variables
    int rankArray[MAX_CAPACITY];
    unsigned long long int passwordArray[MAX_CAPACITY];
    int size;
    double runTime;
    FILE *bubbleSortOutputFile, *insertionSortOutputFile, *selectionSortOutputFile;    
    
    // prompt for size
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    // check for data in array
    if(size > 0) {
        // FOR BUBBLE SORT; read in csv
        importData(rankArray, passwordArray);      
        // open bubble sort output file
        bubbleSortOutputFile = fopen("../reports/bubbleSort.csv", "w+");
        // write bubble sort title to output file
        fprintf(bubbleSortOutputFile, "Array Bubble Sort:\n");
        // run bubble sort
            // function: runBubbleSort()
        runTime = runBubbleSort(rankArray, passwordArray, size);
        // write elapsed time to file
        fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
        // write bubble-sorted data from array to output file
        writeDataToFile(rankArray, passwordArray, size, bubbleSortOutputFile);
        // close bubble sort file
        fclose(bubbleSortOutputFile);
        
        // FOR SELECTION SORT; read in csv
        importData(rankArray, passwordArray);
        selectionSortOutputFile = fopen("../reports/selectionSort.csv", "w+");
        fprintf(selectionSortOutputFile, "Array Selection Sort:\n");
        runTime = runSelectionSort(rankArray, passwordArray, size);
        fprintf(selectionSortOutputFile,
                    "It took %f seconds to sort %d elements. \n", runTime, size);
        writeDataToFile(rankArray, passwordArray, size, selectionSortOutputFile);
        fclose(selectionSortOutputFile);

        // FOR INSERTION SORT; overwrite array for next sort
        importData(rankArray, passwordArray);
        insertionSortOutputFile = fopen("../reports/insertionSort.csv", "w+");
        fprintf(insertionSortOutputFile, "Array Insertion Sort:\n");
        runTime = runInsertionSort(rankArray, passwordArray, size);
        fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
        writeDataToFile(rankArray, passwordArray, size, insertionSortOutputFile);
        fclose(insertionSortOutputFile);
        
        // display success message to screen
        printf("\nSorted data written to bubbleSort.csv selectionSort.csv, and insertionSort.csv");
    }
    
    // otherwise, data was not in array
    else {
        printf("\n\nError: no data found\n");
    }

    // display function success
    printf("\n\nProgram End\n");
    
    // return function success
    return 0;
}

// function implementations

/*
Name: compareData
Process: compares data, returns value greater than 0 if dataOne is larger 
than dataTwo, returns value less than 0 if dataOne is less than dataTwo,
and returns 0 is data are the same.
Function input/parameters: the two values to be compared (int)
Function output/parameters: none
Function output/returned: value as specified (int)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int compareData(int dataOne, int dataTwo) {
    if (dataOne > dataTwo) {
        return 1;
    } 
    else if (dataOne < dataTwo){
        return -1;
    }
    else {
        return 0;
    }
}

void swap(int *dataOne, int *dataTwo) {
    int temp = *dataOne;
    *dataOne = *dataTwo;
    *dataTwo = temp;
}

// provided functions
void writeDataToFile(int rankArray[], unsigned long long int passwordArray[], int size,
                                                                 FILE *fileName) {
    // initialize variables
    int index = 0;
    
    // loop across specified elements
    for(index; index < size; index++) {
        // write data pair to file
        fprintf( fileName, "%d, ", rankArray[index]);
        fprintf( fileName, "%I64llu\n", passwordArray[index]);
    }
    // void, no return
}

void importData(int rankArray[], unsigned long long int passwordArray[]) {
    // initialize variables
    FILE *inputFile;
    int rankIndex = 0, passIndex = 0;
    int rank, strLen;
    unsigned long long int result = 0;
    char password[40];
    char commaCapture;
    int index;
    
    // open file from data folder
    inputFile = fopen("../data/HW_1_DATA_UNSORTED.csv", "r");

    for(rankIndex = 0, passIndex = 0; rankIndex < MAX_CAPACITY;
                                                       rankIndex++, passIndex++) {
        result = 0;
        
        // read in first number
        fscanf( inputFile, "%d", &rank );
        // capture comma
        fscanf( inputFile, "%c", &commaCapture );
        // read in second number
        fscanf( inputFile, "%s", password );

        strLen = strlen(password);
        
        for(index = 0; index < strLen; index++) {
           result = (result * 10 ) + (password[index] - '0');
        }
        
        // put data into array, cast as integer
        rankArray[rankIndex] = rank;
        passwordArray[passIndex] = result;
    }
    
    // close file
    fclose(inputFile);

    // void, no return
}

