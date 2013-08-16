CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
PREFIX=`echo ~`/.lib/ulibtool_

ULIB_INC=-I`echo ~`/.lib/ulib_/include
ULIB_OBJ=`echo ~`/.lib/ulib_/lib/ulib.a

OBJECTS  = mgt/mgt.o 

INC = -Iinclude
BIN = `echo ~`/.mybin

all:    ${OBJECTS} 
	mkdir -p lib
	ar -r lib/ulibtool.a ${OBJECTS}
	# only for linux (not available in Mac OSX)
	ranlib lib/ulibtool.a
#	ar -rscv -o lib/ulib.a ${OBJECTS}
#	ar -rscv -o lib/ustring.a  ustring/ustring.o
#${CC} ${CFLAGS} -shared -fPIC -o ulib.sl $?
	# only for linux (not available in Mac OSX)
	#ctags -R

install:
	mkdir -p ${PREFIX}
	rm -rf ${PREFIX}
	mkdir ${PREFIX}
	cp -R include ${PREFIX}
	mv ${PREFIX}/include/ulibtool.h.org ${PREFIX}/include/ulibtool.h
	cp -R lib ${PREFIX}
	# only for linux (not available in Mac OSX)
	#cp tags ~/.tag
	cd app; make; cd ..
	cp app/mgt ${BIN}/

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${INC} ${ULIB_INC}

clean:
	rm -rf tags
	rm -rf ${OBJECTS}
	rm -rf lib/ulibtool.a

