CC=gcc

dsav: ./src/main.c 
	$(CC) -o ./out/DSAV.out -Wall ./src/main.c -l raylib
