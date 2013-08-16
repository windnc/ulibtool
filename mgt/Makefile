CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
ULIB_INC=-I`echo ~`/.lib/ulib_/include
ULIB_OBJ=`echo ~`/.lib/ulib_/lib/ulib.a
OBJ=mgt.o

all: ${OBJ}
	${CC} ${CFLAGS} -o test main_test.cpp ${OBJ} ${ULIB_INC} ${ULIB_OBJ} -I../include
	${CC} ${CFLAGS} -o mgt-dump main_dump.cpp ${OBJ} ${ULIB_INC} ${ULIB_OBJ} -I../include

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${ULIB_INC} -I../include

clean:
	rm -rf *.o test

install:
	cp mgt-dump `echo ~`/.mybin

