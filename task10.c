#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_0_1() {
    return (double)rand() / RAND_MAX;
}

double random_0_n(double n) {
    return random_0_1() * n;
}

int main() {
    srand(time(NULL));
    printf("Random number in range [0.0, 1.0] -> %.2f\n", random_0_1());
    printf("Random number in range [0.0, n] -> %.2f\n", random_0_n(5.0));
    return 0;
}