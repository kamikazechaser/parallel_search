#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void loadNumbers(char *path, int *array, int size) {
    FILE *fp;
    fp = fopen(path, "r");

    int i = 0;
  	while(i < size) {
  		fscanf(fp, "%d", &array[i]);
      i++;
  	}

    fclose(fp);
}

void linearSearch(int *numbers, int size, int lookingFor) {
    int i, tid;
    int foundNumber = 0;
    double diff;

    double start = omp_get_wtime();

    #pragma omp parallel private(tid) shared(foundNumber)
    {
        tid = omp_get_thread_num();

        #pragma omp for
  	    for (i = 0; i < size; i++) {
  		    if(lookingFor == numbers[i]) {
                foundNumber = 1;
                printf("found at position: %d on processor: %d\n", i, tid);
  	    	}
            if(foundNumber) {
                i = size;
            }
  	    }
    }

    double end = omp_get_wtime();
    diff = end - start;

    printf("time: %.1lf\n", diff*1000000L);
}

int main(void) {
	int SIZE = 25000000;
    int FIND_NUMBER = 1;
	int *numbers = (int*)malloc(SIZE * sizeof(int));

	loadNumbers("25m.txt", numbers, SIZE);
	linearSearch(numbers, SIZE, FIND_NUMBER);
    free(numbers);

	return 0;
}
