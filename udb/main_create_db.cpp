#include "udb.h"

int main()
{
	char *dir = "test-db";
	char *fn = "tmp.db";

	char cmd[128];
	sprintf( cmd, "rm -rf %s", dir );
	system( cmd );

	sprintf( cmd, "mkdir %s", dir );
	system( cmd );

	CUDB db;
	if( db.Open( dir, fn ) == false )	{
		fprintf( stderr, "Fail to open DB (%s/%s)\n", dir, fn );
		return 1;
	}

	fprintf( stderr, "DB %s/%s opened\n", dir, fn );

	db.Close();

	fprintf( stderr, "DB %s/%s closed\n", dir, fn );

	return 0;

}

