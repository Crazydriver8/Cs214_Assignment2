#sets compiler to gcc
COMPILE=gcc
#creates a main program reliant on sorted-list.o and main.o
PGM: sorted-list.o main.o
	#compiles the two files into an executable
	$(COMPILE) sorted-list.o main.o -g -o PGM
#defines the object file reliant on sorted-list.h and sorted-list.c
sorted-list.o: sorted-list.h sorted-list.c
	#compiles sorted-list.c and returns an object file
	$(COMPILE) -c -g sorted-list.c 
#defines the object file reliant on sorted-list.h and main.c
main.o: sorted-list.h main.c
	#compies main.c and returns an object file
	$(COMPILE) -c -g main.c
#
#cleans that crap up
clean:
	rm -rf *.o PGM
