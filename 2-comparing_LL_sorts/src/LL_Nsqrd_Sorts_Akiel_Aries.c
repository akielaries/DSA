// header files
#include <stdio.h>
#include <stdlib.h> // malloc/free
#include <time.h>
#include <string.h>

// global constants
const int MAX_CAPACITY = 150000;

// Data structures
typedef struct PasswordTypeStruct
   {
       
    int rank;
    unsigned long long int  password;
    struct PasswordTypeStruct *nextPtr;
    struct PasswordTypeStruct *prevPtr;

   } PasswordType;

// function declarations
    // for you to write
double runBubbleSort(PasswordType *headPtr);
double runInsertionSort(PasswordType *headPtr);
int compareData(int dataOne, int dataTwo);
void swapData(PasswordType *dataOne, PasswordType *dataTwo);

    // provided
PasswordType *clearLinkedList(PasswordType *wkgPtr);
PasswordType *importData(int size); // provided

void writeDataToFile(PasswordType *headPtr, FILE *fileName);  // provided

// main driver
int main()
{
    // initialize variables
    PasswordType *headPtr = NULL;
    FILE *bubbleSortOutputFile, *insertionSortOutputFile;
    int size;
    double runTime;
   
    // prompt for size
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    // check for data to sort
    if(size > 0 && size <= MAX_CAPACITY)
    {
        // create linked list from input file
            // function: importData
        headPtr = importData(size);
        

        // check for headptr not null
        if(headPtr != NULL)
        {         
            // open output file
            bubbleSortOutputFile = fopen("bubbleSortLL.csv", "w+");

            // write bubble sort title to file
            fprintf(bubbleSortOutputFile, "Linked List Bubble Sort:\n");
            
            // sort data using bubble sort algorithm
                // function: runBubbleSort
            runTime = runBubbleSort(headPtr);
            
            // write elapsed time to file
           fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
         
            // write linked list data to file
            writeDataToFile(headPtr, bubbleSortOutputFile);
            
            // close file
            fclose(bubbleSortOutputFile);
            
            // clear sorted linked list, reset cpdHeadPtr
                // function: clearLinkedList
            headPtr = clearLinkedList(headPtr);
        }
        
        // otherwise, list is null
        else
        {
            // display error message to console
            printf("\nError: No data found. \n");
        }
            
        // read in data again for next sort
            // function: import
         headPtr = importData(size);
        
        if(headPtr != NULL)
        {
            // open output file
            insertionSortOutputFile = fopen("insertionSortLL.csv", "w+");
            
            // write title to file
            fprintf(insertionSortOutputFile, "Linked List Insertion Sort:\n");

            // sort data using insertion sort algorithm  
                // function: runInsertionSort
            runTime = runInsertionSort(headPtr);

           fprintf(insertionSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);            

            // write linked list data to file
            writeDataToFile(headPtr, insertionSortOutputFile);
            
            // close output file  
            fclose(insertionSortOutputFile);
            
            // clear all linked lists (original and copied) 
                // function: clearLinkedList  
            headPtr = clearLinkedList(headPtr);

                    
        }
        
        // otherwise, list is null
        else
        {
            // display error message to console
            printf("\nError: No data found. \n");
        }
        
        // display program success to console.
         printf("\nData written to bubbleSortLL.csv and insertionSortLL.csv\n");
    }
    
    // Otherwise, size is not a valid input
    else
    {
        printf("Incorrect input.\n");
    }
    
    printf("\nEnd program\n");
    
    // return function success
    return 0;
}

// function implementations

/*
Name: compareData
Process: compares data, returns value greater than 0 is dataOne is larger than dataTwo,
                             returns value less than 0 if dataOne is less than dataTwo,
                             and returns 0 is data are the same.
Function input/parameters: the two values to be compared (int)
Function output/parameters: none
Function output/returned: value as specified (int)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int compareData(int dataOne, int dataTwo)
{
    if (dataOne > dataTwo)
    {
        return 1;
    }
    else if (dataOne < dataTwo) 
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

/*
Name: runBubbleSort
Process: sorts the data using the bubble sort algorithm
Function input/parameters: headPtr of list to be sorted
Function output/parameters: none
Function output/returned: updated headPtr of sorted list
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
double runBubbleSort(PasswordType *headPtr)
{
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    int swapped;
    // temp var for setting ptrs that need swapping equal to
    int tempRank = 0;
    unsigned long long int tempPass = 0;
    PasswordType *startPtr; 
    PasswordType *endPtr = NULL;
    
    startTime = clock();
    
    do 
    {
        // swapped variable for before/after sort is ran
        swapped = 0;
        // start pointer
        startPtr = headPtr;
        
        // while nextptr is not end
        while (startPtr->nextPtr != endPtr)
        {
            // call compareData, comparing start and next
            if (compareData(startPtr->rank, 
                        startPtr->nextPtr->rank) == 1) 
            {    
                // swap start ptr and next if startPtr > startPtr next
                // using temp variable, swap start and next
                tempRank = startPtr->rank;
                startPtr->rank = startPtr->nextPtr->rank;
                startPtr->nextPtr->rank = tempRank;
                
                // same logic as above, swapping rank assignments
                // the password values
                tempPass = startPtr->password;
                startPtr->password = startPtr->nextPtr->password;
                startPtr->nextPtr->password = tempPass;
                // if condition hit swapped 
                swapped = 1;
            
            }
            // set start = to next 
            startPtr = startPtr->nextPtr;
        
        }
        // set end = to start to begin process over
        endPtr = startPtr;
    
    }
    // continue algorithm until 
    while (swapped);

    // end time
    endTime = clock();
    
    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    
    return totalTime;

}


/*
Name: runInsertionSort
Process: sorts the data using the insertion sort algorithm
Function input/parameters: headPtr of list to be sorted
Function output/parameters: none
Function output/returned: updated headPtr of sorted list
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
double runInsertionSort(PasswordType *headPtr)
{
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    // temp var for setting ptrs that need swapping equal to
    int tempRank = 1;
    unsigned long long int tempPass = 1;
    PasswordType *startPtr;
    PasswordType *endPtr = NULL;
    startPtr = headPtr;
    
    startTime = clock();
    
    // while startPtr is not empty
    while (startPtr != NULL) 
    { 
        // get next node
        // setting endPtr = the start next 
        endPtr = startPtr->nextPtr;
        
        // update node val when consecutive nodes not sorted
        // call compareData for end and previous
        while (endPtr != NULL 
                && endPtr->prevPtr != NULL && (
                compareData(endPtr->rank, endPtr->prevPtr->rank) == -1))
        {
            // swap nodes
            tempRank = endPtr->rank;
            endPtr->rank = endPtr->prevPtr->rank;
            endPtr->prevPtr->rank = tempRank;

            // apply same logic as above for swapping passwords 
            tempPass = endPtr->password;
            endPtr->password = endPtr->prevPtr->password;
            endPtr->prevPtr->password = tempPass;

            // visit prev node
            endPtr = endPtr->prevPtr;
        }
        // set start to next
        startPtr = startPtr->nextPtr;
    }
    // end time
    endTime = clock();
    
    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    
    return totalTime;

}

// Provided Functions
PasswordType *clearLinkedList(PasswordType *wkgPtr)
{
    PasswordType *ptr = wkgPtr;

    while( ptr != NULL )
    {
        wkgPtr = wkgPtr->nextPtr;

        free(ptr);

        ptr = wkgPtr;
    }
    
    return NULL;

}

PasswordType *importData(int size)
{
   // initialize variables
   FILE *inputFile;
   int index, strIndex, rank, strLen;
   unsigned long long int result = 0;
   char comma, password[40];
   PasswordType *previousNodePtr, *nextNodePtr, *headPtr = NULL;
   
   // prime loop
   previousNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
   
   // open file
   inputFile = fopen("HW_1_DATA_UNSORTED.csv", "r");
   
   // read in first number
    fscanf( inputFile, "%d", &rank );
    
    // capture comma
    fscanf( inputFile, "%c", &comma );
    
    // read in second number
    fscanf( inputFile, "%s", password );
    
    strLen = strlen(password);
        
    for(strIndex = 0; strIndex < strLen; strIndex++)
    {
       result = (result * 10 ) + (password[strIndex] - '0');
    }
    
    // put data into node
    previousNodePtr->rank = rank;
    previousNodePtr->password = result;
    previousNodePtr->nextPtr = NULL;
    previousNodePtr->prevPtr = NULL;

    // set headPtr
    headPtr = previousNodePtr;
    
   // loop to import up to size
   for(index = 1; index < size; index++)
   {
       result = 0;
       
       // create next node
       nextNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
       
       // assign next ptr and previous node ptr
       previousNodePtr->nextPtr = nextNodePtr;
       nextNodePtr->prevPtr = previousNodePtr;
       
       // read in first number
       fscanf( inputFile, "%d", &rank );
        
       // capture comma
       fscanf( inputFile, "%c", &comma );
        
       // read in second number
       fscanf( inputFile, "%s", password );
       
        strLen = strlen(password);
        
        for(strIndex = 0; strIndex < strLen; strIndex++)
        {
           result = (result * 10 ) + (password[strIndex] - '0');
        }
                
       // put data into node
       nextNodePtr->rank = rank;
       nextNodePtr->password = result;
       nextNodePtr->nextPtr = NULL;
       
       previousNodePtr = nextNodePtr;
   }
   
   fclose(inputFile);
   
   // return updated headPtr
    return headPtr;
}

void writeDataToFile(PasswordType *headPtr, FILE *fileName)
{
    // initialize variables
    PasswordType *wkgPtr = headPtr;
    
    // loop across specified elements
    while(wkgPtr != NULL)
    {
        // write data pair to file
        fprintf( fileName, "%d, %I64llu\n", wkgPtr->rank, wkgPtr->password);
        
        wkgPtr = wkgPtr->nextPtr;

    }
    
    // void, no return
}
