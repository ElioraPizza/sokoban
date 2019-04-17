file: file.c
	gcc -o fileex file.c -lncursesw -std=c99 -Wall
	./fileex
test: fileex
	./fileex
