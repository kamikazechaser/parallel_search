#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define int long long int

// Load all number from "path" to "array"
void loadNumbers(char *path, int *array, int size) {
  FILE *fp;
  fp = fopen(path, "r");

  int i = 0;
  while (i < size) {
    fscanf(fp, "%d", &array[i]);
    i++;
  }

  fclose(fp);
}

// Use Linear Search to look for number "lookingFor" in array "numbers"
void linearSearch(int *numbers, int size, int lookingFor) {
  double diff;
  double start = omp_get_wtime();
  // Linear Search
  int i;
  for (i = 0; i < size; i++) {
    if (lookingFor == numbers[i]) {
      // printf("DEBUG :: Found Number :: I = %d\n", i);
      i = size;
    }
  }
  double end = omp_get_wtime();
  diff = end - start;
  printf("Time: %.1lf", diff * 1000000L);
}

int main(int argc, char *argv[]) {
  // Max size 100,000 (.txt file contains that many elements)
  int SIZE = atoi(argv[1]);
  // Test cases:
  // Number 1 is at the end of the array (length - 1)
  // Number 2 is at the beginning (index 7)
  int FIND_NUMBER = 1;
  int *numbers = (int *)malloc(SIZE * sizeof(int));
  loadNumbers(argv[2], numbers, SIZE);
  linearSearch(numbers, SIZE, FIND_NUMBER);

  free(numbers);
  return 0;
}
