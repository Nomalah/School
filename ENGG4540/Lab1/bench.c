#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define N 10000000

double cube_root(double x);

int main() {
    double x = 0.0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 1; i < N; i++) {
        x += cube_root(i);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Result: %f\n", x);
    printf("Time: %f\n", cpu_time_used);
    return 0;
}


double cube_root(double x) {
    double r = x;

    // Newton's method
    // r = r - f(r)/f'(r)
    // r = r - (r^3 - x)/(3r^2)
    for (int i = 0; i < 100; i++) {
        double r_old = r;
        r = r - (r*r*r - x)/(3*r*r);
        double diff = r - r_old;
        if (fabs(diff) < 1e-6) {
            break;
        }
    }

    return r;
}


