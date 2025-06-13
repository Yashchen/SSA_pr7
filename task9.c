#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double time_elapsed;

    start = clock();

    for (volatile int i = 0; i < 1000000; i++);

    end = clock();

    time_elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("Execution time: %.3f ms\n", time_elapsed);

    return 0;
}