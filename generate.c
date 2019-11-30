#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    FILE *fp;
    fp = fopen("10m.txt", "w");

    for (int i = 10000000; i > 0; i--)
        fprintf(fp, "%d ", i);
}
