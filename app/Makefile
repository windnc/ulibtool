CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings

ULIB_INC=-I`echo ~`/.lib/ulib_/include
ULIB_OBJ=`echo ~`/.lib/ulib_/lib/ulib.a

ULIBTOOL_INC=-I`echo ~`/.lib/ulibtool_/include
ULIBTOOL_OBJ=`echo ~`/.lib/ulibtool_/lib/ulibtool.a

INC=${ULIBTOOL_INC} ${ULIB_INC}
OBJ=${ULIBTOOL_OBJ} ${ULIB_OBJ}

BIN=`echo ~`/.mybin

all: 
	${CC} ${CFLAGS} -o mgt main_mgt.cpp \
		${INC} \
		${OBJ} 

install:
	cp mgt ${BIN}/

clean:
	rm -rf *.o test

