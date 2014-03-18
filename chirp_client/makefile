COMPILER = gcc
FLAGS = -W -Wall

chirp: chirp.o
	${COMPILER} ${FLAGS} -o chirp chirp.o

%.o: %.c
	${COMPILER} ${FLAGS} -c $*.c

clean:
	rm -f *.o *~ chirp

test:
	./chirp "Hello World"

