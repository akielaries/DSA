// header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global constants
const int MAX_NODES = 150000;

// data structure, BST node
typedef struct PasswordTypeStruct
   {
    int rank;
    unsigned long long int password;
    struct PasswordTypeStruct *leftChildPtr;
    struct PasswordTypeStruct *rightChildPtr;
   } PasswordType;
   
 
// function declarations 

// for students to write

PasswordType *clearBST(PasswordType *wkgPtr);
void displayTreeInOrder(PasswordType *wkgPtr, FILE *outputFile);
PasswordType *initializeNodeFromData(int rankInput, unsigned long long int passInput);
PasswordType *insert(PasswordType *wkgPtr, PasswordType *inNodePtr);

// provided function
PasswordType *importData(int size, double *runTime);


// main driver
int main()
{
    // initialize variables
    int size;
    double runTime;
    PasswordType *rootPtr = NULL;
    FILE *outputFile;
    
    // prompt for size
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    // check for correct size input
    if(size >= 1 && size <= MAX_NODES)
    {
        // import data, create search tree
        rootPtr = importData(size, &runTime);

        
        // check for return from import not null
        if(rootPtr != NULL)
        {
            // open output file
            outputFile = fopen("BSTSorted.csv", "w+");
            
            // write run time to file
            fprintf(outputFile, "It took %f seconds to sort %d elements.\n",
                                                               runTime, size);
            
            // write data to output file
            displayTreeInOrder(rootPtr, outputFile);
            
            // close output file
            fclose(outputFile);
            
            // display file name to screen
            printf("\nData written to BSTSorted.csv\n");
            
            // clear tree
            rootPtr = clearBST(rootPtr);
        }  
        // otherwise, tree is empty
        else
        {
            // display no data message
            printf("\nError: no data found\n");
        }
    }   
    // otherwise incorrect input for size
    else
    {
        // display error message for size
        printf("\nIncorrect input.\n");
    }
    
    
    // show program end
    printf("\nEnd program\n");
    
    // return program success
    return 0;
}

// function implementations

// for students to write
/*
Name: clearBST
Process: recursively clears the tree.
Function input/parameters: working pointer for recursion
Function output/parameters: none
Function output/returned: NULL
Device input/file: none
Device output/monitor: none
Dependencies: free, clearBST (recursive)
deletes using post order LRN (LEFT, RIGHT, NODE)
*/

PasswordType *clearBST(PasswordType *wkgPtr)
{
    // recursive call to left and right
    if (wkgPtr != NULL)
    {
        // recursively call clear left side
        wkgPtr->leftChildPtr = clearBST(wkgPtr->leftChildPtr);    
        //clearBST(wkgPtr->leftChildPtr);
        // recursively call clear right side
        wkgPtr->rightChildPtr = clearBST(wkgPtr->rightChildPtr);
        // free wkgPtr
        free(wkgPtr);
    }
    return wkgPtr;
}

/*
Name: displayTreeInOrder
Process: recursively writes binary search tree data to output file using inorder traversal.
Function input/parameters: working pointer for recursion, file name
Function output/parameters: none
Function output/returned: none
Device input/file:none
Device output/file: file with BST data written to it
Dependencies: fprintf, displayTreeInOrder
LNR (LEFT, NODE, RIGHT) in order traversal
*/
void displayTreeInOrder(PasswordType *wkgPtr, FILE *outputFile)
{
    // check for working ptr not null
    if (wkgPtr != NULL)
    {
        // recursive call to the left
        displayTreeInOrder(wkgPtr->leftChildPtr, outputFile);
        // write data from current node to file in format: rank, password
        fprintf(outputFile, "%d, %I64llu\n", wkgPtr->rank, wkgPtr->password);
        // recursive call to the right
        displayTreeInOrder(wkgPtr->rightChildPtr, outputFile);
    }
    // void, no return
}
/*
Name: initializeNodeFromData
Process: creates a node, places data into node, sets child pointers to NULL, returns pointer to
                                                                                   created node.
Function input/parameters: rankInput (int), passInput (unsigned long long int)
Function output/parameters: none
Function output/returned: pointer to created node
Device input/file: none
Device output/monitor: none
Dependencies: malloc, sizeof
*/
PasswordType *initializeNodeFromData(int rankInput,
                                               unsigned long long int passInput)
{
    // initialize variables
    PasswordType *newNodePtr;

    // create a node using malloc()
    newNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
        
    // put rank and password into the node
    newNodePtr->rank = rankInput;
    newNodePtr->password = passInput;

    // assign both ptrs to null
    newNodePtr->leftChildPtr = NULL;
    newNodePtr->rightChildPtr = NULL;

    //return NULL; // temporary return stub
    return newNodePtr;
}

/*
Name: insert
Process: recursively searches for a place to insert node into search tree. 
Once location is found, node is inserted. If data is already in tree,
                                                             no action is taken.
Function input/parameters: wkgPtr for recursion, pointer to data for insertion
Function output/parameters: none
Function output/returned: wkgPtr for that recursion
Device input/file: none
Device output/monitor: none
Dependencies: insert (recursive)
*/

PasswordType *insert(PasswordType *wkgPtr, PasswordType *inNodePtr)
{
   
    // check for wkgPtr != NULL
    if (wkgPtr != NULL)
    {
        // check if data to be inserted is smaller than wkgPtr data
        if (inNodePtr->rank < wkgPtr->rank)
        {
            // recursive call to the left
            wkgPtr->leftChildPtr = insert(wkgPtr->leftChildPtr, inNodePtr);
        }
        // otherwise if data to be inserted is larger than wkgPtr data
        else if (inNodePtr->rank > wkgPtr->rank)
        {
            // recursive call to the right
            wkgPtr->rightChildPtr = insert(wkgPtr->rightChildPtr, inNodePtr);
        }
    }
    // otherwise wkgPtr is null (reached end of TREE)
    else if (wkgPtr == NULL)
    {
        // point wkgPtr at the inNodePtr
        wkgPtr = inNodePtr;
    }       

    return wkgPtr; // temporary return stub
    
}


// provided function
/*
Name: importData
Process: Opens input file, reads in a rank, password pair. Data is set in a node,
and then inserted into the binary search tree, process is repeated until until
                                                      specified size is reached.
Function input/parameters: the amount of data to be read in
Function output/parameters: length of time to sort data/create BST
Function output/returned: pointer to root node
Device input/file: input file placed in current working directory
Device output/monitor: none
Dependencies: initializeNodeFromData, insert, fscanf, fopen, fclose
*/
PasswordType *importData(int size, double *runTime)
{
    // initialize variables
    PasswordType *rootPtr = NULL, *insertNodePtr = NULL;
    FILE *inputFilePtr;
    int index, rank;
    char comma;
    long long unsigned int password;
    clock_t startTime, endTime;
    
    // start timer
    startTime = clock();
    
    // open input file
    inputFilePtr = fopen("BinarySearchTreeData.csv", "r");
    
    // loop across the number of nodes to read in
    for(index = 0; index < size; index++)
    {
        // read in data pair
        fscanf(inputFilePtr, "%d", &rank);
        fscanf(inputFilePtr, "%c", &comma);
        fscanf(inputFilePtr, "%I64llu", &password);
        
        // create node and set data
        insertNodePtr = initializeNodeFromData(rank, password);
        
        // call insert to place node
        rootPtr = insert(rootPtr, insertNodePtr);

    }

    // close data file
    fclose(inputFilePtr); 
    
    // end timer
    endTime = clock();
    
    // return time using dereferencing
    *runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    
    // return root node
    return rootPtr;
}
