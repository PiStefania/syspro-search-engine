CC = gcc -g
FILES = main.c variousMethods.c index.c invertedIndex.c
OBJECTS = main.o variousMethods.o index.o invertedIndex.o
OUT = minisearch
HEADERS = variousMethods.h index.h invertedIndex.h


all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES) -lm
	make clean
	
main.o: main.c
	$(CC) -c main.c

variousMethods.o: variousMethods.c
	$(CC) -c variousMethods.c
	
index.o: index.c
	$(CC) -c index.c
	
invertedIndex.o: invertedIndex.c
	$(CC) -c invertedIndex.c
	
clean:
	rm -f $(OBJECTS)