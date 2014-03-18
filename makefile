COMPILER = gcc
FLAGS = -W -Wall

chirplistener: chirp_listener.o
	${COMPILER} ${FLAGS} -o chirplistener chirp_listener.o

%.o: %.c
	${COMPILER} ${FLAGS} -c $*.c

clean:
	rm -f *.o *~ chirplistener

start:
	./chirplistener

