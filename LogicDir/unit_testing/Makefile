CC = clang
CFLAGS = -c -Wall -Wextra -O2
LFLAGS = -Wall -Wextra
COLLECTION_DEPS = collection.h
TEST_DEPS = testHandler.h testPrinter.h testPropogate.h
#
# main.exe: main.o unitPropogate.o parser.o printer.o
# 	${CC} ${LFLAGS} main.o unitPropogate.o parser.o -o main.exe

testModule.exe: testModule.o printer.o collectionHandler.o unitPropogation.o
	${CC} ${LFLAGS} testModule.o printer.o	collectionHandler.o unitPropogation.o

testModule.o: ${TEST_DEPS} testModule.c
	${CC} ${CFLAGS}	testModule.c

printer.o: ${COLLECTION_DEPS} printer.c
	${CC} ${CFLAGS} printer.c

collectionHandler.o: ${COLLECTION_H} collectionHandler.c
	${CC} ${CFLAGS} collectionHandler.c

unitPropogation.o: ${COLLECTION_H} unitPropogation.c
	${CC} ${CFLAGS} unitPropogation.c
