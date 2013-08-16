CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings

DB_INC=-I/opt/local/include/db47/
DB_LIB=/opt/local/lib/db47/libdb.a
OBJ=udb.o

all: ${OBJ}
	${CC} ${CFLAGS} -o create_db main_create_db.cpp ${OBJ} ${DB_INC} ${DB_LIB}
	${CC} ${CFLAGS} -o find_data main_find_data.cpp ${OBJ} ${DB_INC} ${DB_LIB}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${DB_INC} 

clean:
	rm -rf *.o create_db find_data test-db

