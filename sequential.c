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
    int i;
    double diff;

    double start = omp_get_wtime();

	for (i = 0; i < size; i++) {
		if(lookingFor == numbers[i]) {
            printf("found at position:  %d\n", i);
            i = size;
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
