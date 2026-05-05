all: cube

cube: cube.c
	gcc -o cube cube.c -lm
