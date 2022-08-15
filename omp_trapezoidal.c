#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#endif

void Trap(double a, double b, int n, double* global_result_p);
double f(double const x);

int main(int argc, char* argv[])
{
    double global_result = 0.0;
    double a, b;
    int    n;
    int    thread_count;

    thread_count = strtol(argv[1], NULL, 10);
    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
#pragma omp parallel num_threads(thread_count)
    Trap(a, b, n, &global_result);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.14e\n", 
        a, b, global_result);
    return 0;
}   /* main */

void Trap(double a, double b, int n, double* global_result_p)
{
    double h, x, my_result;
    double locaL_a, locaL_b;
    int i, local_n;
#ifdef _OPENMP
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
#else
    int my_rank = 0;
    int thread_count = 1;
#endif

    h = (b-a)/n;
    local_n = n/thread_count;
    locaL_a = a +  my_rank * local_n * h;
    locaL_b = locaL_a + local_n * h;
    my_result = (f(locaL_a) + f(locaL_b))/2.0;
    for (i = 1; i <= local_n-1; ++i)
    {
        x = locaL_a + i*h;
        my_result += f(x);
    }
    my_result = my_result * h;

#pragma omp critical
    *global_result_p += my_result;
}   /* Trap */

// function f: f(x) = x;
double f(double const x)
{
    return x; 
}   /* f */