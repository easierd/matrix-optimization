dgemm: dgemm.c
	gcc -O3 -mavx2 -march=native -o dgemm dgemm.c
