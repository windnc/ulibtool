#ifndef __UDB__
#define __UDB__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "db.h"

class CUDB {
public:
	CUDB();
	~CUDB();
public:

	bool Open( char *dir, char *fn );
	bool IsOpened();
	bool IsOpen();
	void Close();
	int GetNumRecord();
	bool HaveKey( char *key );
	bool AddKey( char *key, char *data );
	bool GetData( char *key, char *data, int size );
	void Abort();

private:
	DB *db;
	DB_ENV *env;
	DB_TXN *txn;

	bool isOpened;



};



#endif
