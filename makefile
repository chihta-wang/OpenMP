omp_file = omp_trapezoidal_v2
${omp_file} : 
	g++ -g -Wall -fopenmp -o ${omp_file} ${omp_file}.cpp
clean:
	rm ${omp_file}