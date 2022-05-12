all: exec

c-files: char2ascii.c
	gcc -g -c -o char2ascii.o char2ascii.c

exec: c-files char2ascii.o
	gcc -g char2ascii.o -o char2ascii

.PHONY: clean
clean:
	rm -rf ./*.o main