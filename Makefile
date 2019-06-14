krash.o : krash.c
	gcc -o krash krash.c -w
clean:
	rm -f *.o
