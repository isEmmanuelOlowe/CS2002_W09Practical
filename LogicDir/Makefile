CC = clang
CFLAGS = -c -Wall -Wextra -O2
LFLAGS = -Wall -Wextra
COLLECTION_DEPS = collection.h

main: main.o unitPropogate.o collectionHandler.o printer.o
	${CC} ${LFLAGS} main.o unitPropogate.o parser.o -o main

main.o: ${COLLECTION_DEPS} main.c
	${CC} ${CFLAGS} main.c

collectionHandler.o: ${COLLECTION_H} collectionHandler.c
	${CC} ${CFLAGS} collectionHandler.c

exhaustivePropogation.o: ${COLLECTION_H} handler.h printer.h exhaustivePropogate.c
	${CC} ${CFLAGS} exhaustivePropogation.c

printer.o: ${COLLECTION_DEPS} printer.c
	${CC} ${CFLAGS} printer.c
