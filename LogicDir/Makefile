CC = clang
CFLAGS = -c -Wall -Wextra -O2
LFLAGS = -Wall -Wextra
COLLECTION_DEPS = collection.h

all: main

main: main.o exhaustivePropagation.o collectionHandler.o printer.o
	${CC} ${LFLAGS} main.o exhaustivePropagation.o collectionHandler.o printer.o -o main

main.o: ${COLLECTION_DEPS} propagate.h main.c
	${CC} ${CFLAGS} main.c

collectionHandler.o: ${COLLECTION_H} collectionHandler.c
	${CC} ${CFLAGS} collectionHandler.c

exhaustivePropagation.o: ${COLLECTION_H} handler.h printer.h exhaustivePropagation.c
	${CC} ${CFLAGS} exhaustivePropagation.c

printer.o: ${COLLECTION_DEPS} printer.c
	${CC} ${CFLAGS} printer.c

clean:
	rm *.o main
