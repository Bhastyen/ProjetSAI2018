CC=gcc
OPTION=-Wall


all: app clean


app: main.c point.o  point.o paraRectangle.o snake.o camera.o
	$(CC) $(OPTION) main.c point.o paraRectangle.o snake.o camera.o -o app -lglut -lGLU -lGL -lm

point.o: point.c point.h
	$(CC) $(OPTION) -c point.c -o point.o

matrice.o: matrice.c matrice.h
	$(CC) $(OPTION) -c matrice.c -o matrice.o

paraRectangle.o: paraRectangle.c paraRectangle.h
	$(CC) $(OPTION) -c paraRectangle.c paraRectangle.h

snake.o: snake.c snake.h
	$(CC) $(OPTION) -c snake.c snake.h

camera.o: camera.c camera.h
	$(CC) $(OPTION) -c camera.c

clean:
	rm -f *.o *~
