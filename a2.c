/**
 * Description: This module takes in 2 8 x 8 matrices as input, and with the help
 *              of child processes, it computes the dot product for each row in A
 *              and each column in W. The child returns the computed products
 *              through a pipe, back to the parent process, which stores all the
 *              in a result array, R. The R matrix is then printed as the result.
 * Author Names: Janani Pandurangan and Shirley Li
 * Author Emails: janani.pandurangan@sjsu.edu, shirley.li@sjsu.edu
 * Last Modified Date: 9/25/2023
 * Creation Date: 9/19/2023
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


#define NUM_ROWS 8
#define NUM_COLS 8

/**
* Collects and reads input files into the 8 x 8 matrices. Then, spawns a new process for each
* row by calling fork(). Collects the result from child process and prints the result.
* @param argc - the number of inputs, which includes program's name
* @param argv - the terminal input, which is the file names
* @return 0 - if the program runs as it should, this will return a 0 
*/
int main(int argc, char *argv[]){

    // to calculate the time taken from start to finish of this program
    struct timespec start, finish;

    // to hold finish - start in seconds 
    double elapsed;

    // stores the start time of the program
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // declare the A, W, and R matrices (R = result)
    int A[NUM_ROWS][NUM_COLS];
    int W[NUM_ROWS][NUM_COLS];
    int R[NUM_ROWS][NUM_COLS];

    // declares an int with the number of child processes to create
    int numProcesses = NUM_COLS;

    // stores the two ends of the pipe used to communicate between the child and the parent process
    // created a 2d array of size 8 x 2, 8 pipes and 2 ends each
    // did this to reduce number of statements checking the num of each process
    int fd[numProcesses][2];


    // argc = 2 files + program name, thus we need to check if argc - 1 == 2, if not error
    if (argc - 1 != 2) {
        printf("Error: expecting 2 files as input\n");
        exit(1);
    }

    // creating file pointers for each file, A.txt and W.txt
    FILE *fpA = fopen(argv[1], "r");
    FILE *fpW = fopen(argv[2], "r");

    // checks if files can be opened
    if (fpA == NULL || fpW == NULL) {
        printf("Error: cannot open file\n");
        exit(1);
    }

    // initializes all arrays with 0's to prevent errors when reading 
    for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLS; j++){
            A[i][j] = 0;
            W[i][j] = 0;
            R[i][j] = 0;
        }
    }


    /* note: populated A and W matrices separately, even though they are 8 x 8 matrices
    *  they do not have matching dimensions in the files, thus populating them separately
    *  would be easier
    */ 
   

    // populates the A matrix by reading the A.txt file
    for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLS; j++){

            // scans the next number in the A.txt file
            fscanf(fpA, "%d", &(A[i][j]));

            // gets the next character in the line, if it is newline : break, else continue
            int numA = fgetc(fpA);

            if(numA == '\n'){
                break;
            }
        }
    }
    

    // populates the W matrix by reading the W.txt file 
    for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLS; j++){
            
            // scans the next number in the W.txt file 
            fscanf(fpW, "%d", &(W[i][j]));

            // gets the next character in the line, if it is newline : break, else continue
            int numW = fgetc(fpW);

            if(numW == '\n'){
                break;
            }

        }
    }

    // closes the file pointers
    fclose(fpA);
    fclose(fpW);

    
    // to make sure that each row has it's own process to compute the result using for loop
   for(int row = 0; row < numProcesses; row++){

        // creates the pipe for the row and checks if it is created correctly, if not it prints an error message and exits
        if(pipe(fd[row]) == -1){
            fprintf(stderr, "Pipe failed to be created");
            exit(1);
        }

        // spawn new child process
        pid_t p = fork();

        if(p < 0){ // if pid of child < 0, that means fork failed

            fprintf(stderr, "Error: fork failed");
            exit(1);

        } else if(p == 0){  // if it is a child process, and if it is spawned correctly

            // close the reading end of the pipe
            close(fd[row][0]);

            // stores the computed ith dot product of A[row] and W[col], col = i
            int row_products[NUM_ROWS];

            // initialize all elements in row_products to 0
            for(int i = 0; i < NUM_ROWS; i++){
                row_products[i] = 0;
                
            }

            int num = 0;
            for(int i = 0; i < NUM_ROWS; i++){
                for(int j = 0; j < NUM_ROWS; j++){
                    // computes the dot product A's row vector and W's col vector
                    row_products[num] += (A[row][j] * W[j][i]);
                }
                num++;
            }

            // write the products array through the pipe and to the parent process
            write(fd[row][1], &row_products, sizeof(row_products));

            // close the writing end of the pipe
            close(fd[row][1]);

            // exit successfully out of the child process
            exit(0);
        } 
    }

    // gets the status and the pid of the child that finished executing
    int status;
    int pid_finished;
    int row = 0;

    // waits until all child processes are done to get the result
    while((pid_finished = wait(&status)) > -1){

        // if child terminated correctly
        if(WIFEXITED(status)){
            // array that stores the received dot products from child 
            int child_products[NUM_COLS];

            // read and store the contents sent through pipe in array
            read(fd[row][0], &child_products, sizeof(child_products));

            // closes the reading end after the child_products array is read
            close(fd[row][0]);

            // populate the R (result) array with the child products from that row
            for(int i = 0; i < NUM_ROWS; i++){ 
                R[row][i] = child_products[i];
            }

            // increment the row
            row++;

        // if child terminated abnormally
        } else if (WIFSIGNALED(status)){

            // print an error message with the child pid and its status code
            fprintf(stderr, "Child %d terminated abnormally with status code %d\n", pid_finished, status);
            exit(1);
        }
    }

    // the below code chunk prints out the resulting matrix, R
    printf("\nResult of A*W = [\n");

    for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLS; j++){
            printf("%d ", R[i][j]);
        }

        printf("\n");
    }

    printf("]\n");

    // gets the ending time of the program in second
    clock_gettime(CLOCK_MONOTONIC, &finish);

    // calculates the elapsed time, finish - start, with more precision (from time example)
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Runtime %f seconds\n", elapsed);

    // exits out of the program successfully
    exit(0);
}
