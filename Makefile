CC=gcc

all:./src/main.c ./src/rendering.c ./src/helpers.c ./src/content.c ./src/array_sorts.c
	$(CC) -o ./out/DSAV.out -Wall ./src/main.c ./src/rendering.c ./src/helpers.c ./src/content.c ./src/array_sorts.c -l raylib

dsav: ./src/main.c 
	$(CC) -o ./out/DSAV.out -Wall ./src/main.c -l raylib
