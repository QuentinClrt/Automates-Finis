
CC = g++
CFLAGS = -Wall
DEPS = automate.h algorithm.h
OBJ = automate.o algorithm.o main.o

%.o : %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

lanceur : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


clean :
	rm -f *.o
