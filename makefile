omp_file = omp_trapezoidal_v2
${omp_file} : 
	gcc -g -Wall -fopenmp -o ${omp_file} ${omp_file}.c
clean:
	rm ${omp_file}