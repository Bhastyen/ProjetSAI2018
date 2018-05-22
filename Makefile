CC=gcc
OPTION=-Wall


all: app clean


app: main.c mon_allocation.o point.o file.o  paraRectangle.o snake.o
	$(CC) $(OPTION) main.c mon_allocation.o point.o file.o paraRectangle.o snake.o -o app -lglut -lGLU -lGL -lm

mon_allocation.o: ./module/mon_allocation.c ./module/mon_allocation.h
	$(CC) $(OPTION) -c ./module/mon_allocation.c -o mon_allocation.o

file.o: ./module/file.c ./module/file.h
	$(CC) $(OPTION) -c ./module/file.c -o file.o

point.o: point.c point.h
	$(CC) $(OPTION) -c point.c -o point.o

matrice.o: matrice.c matrice.h
	$(CC) $(OPTION) -c matrice.c -o matrice.o

paraRectangle.o: paraRectangle.c paraRectangle.h
	$(CC) $(OPTION) -c paraRectangle.c paraRectangle.h

snake.o: snake.c snake.h
	$(CC) $(OPTION) -c snake.c snake.h

clean:
	rm -f *.o *~
