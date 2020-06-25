#include <time.h>
#include <stdio.h>

int main1()
{
    clock_t start = clock();

    // code ...

    clock_t end = clock();

    double dur = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    printf("time: %.2f ms", dur);
    return 0;
}