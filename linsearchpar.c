#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int long long int

// read dataset into an array
void loadNumbers(char * path, int * array, int size) {
    FILE * fp;
    fp = fopen(path, "r");
    int i = 0;
    while (i < size) {
        fscanf(fp, "%d", & array[i]);
        i++;
    }
}

// linear search function
void linearSearch(int * numbers, int size, int lookingFor) {
    double diff;
    int tid, i;
    
    int foundNumber = 0;
    double start = omp_get_wtime();
    
    // do in parallel
    #pragma omp parallel num_threads(2) private(tid) shared(foundNumber)
    {
        tid = omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < size; i++) {
            if (lookingFor == numbers[i]) {
                foundNumber = 1;
                printf("found at position: %d on processor: %d\n", i, tid);
            }
            if (foundNumber) {
                i = size;
            }
        }
    }
    
    double end = omp_get_wtime();
    diff = end - start;
    
    printf("time: %.1lf\n", diff*1000000L);
}

int main(int argc, char * argv[]) {
    int SIZE = atoi(argv[1]);
    int FIND_NUMBER = 1;
    
    int * numbers = (int*) malloc(SIZE * sizeof(int));
    
    loadNumbers(argv[2], numbers, SIZE);
    linearSearch(numbers, SIZE, FIND_NUMBER);
    free(numbers);
    
    return 0;
}
