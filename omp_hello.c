#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void Hello(void); /* thread function */

int main(int argc, char* argv[])
{   
    if (argc != 2)
    {
        printf("Enter the number of threads you want to create!\n");
        exit(1);
    }

    /* Get the number of threads from command line */
    int thread_count = strtol(argv[1], NULL, 10);
    if (thread_count <= 0)
    {
        printf("The number of threads should be positive!\n");
        exit(1);
    }

# pragma omp parallel num_threads(thread_count)
    Hello();

    return 0;
}   /* main */

void Hello(void)
{
#ifdef _OPENMP
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
#else
    int my_rank = 0;
     int thread_count = 1;
#endif
    printf("Hello from %d of %d\n", my_rank, thread_count);
}   /* Hello */