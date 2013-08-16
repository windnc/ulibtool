#include "udb.h"

int main()
{
	char *dir = "test-db";
	char *fn = "tmp.db";

	CUDB db;
	if( db.Open( dir, fn ) == false )	{
		fprintf( stderr, "Fail to open DB (%s/%s)\n", dir, fn );
		return 1;
	}

	fprintf( stderr, "DB %s/%s opened\n", dir, fn );

	char key[128];
	char data[128];
	strcpy( key, "swlee" );
	strcpy( data, "swlee@nlp.korea.ac.kr" );

	fprintf( stderr, "Finding key '%s'... ", key );
	if(	db.GetData( key, data, 128 ) == true )	{
		fprintf( stdout, "[%s]\n", data );
	}
	else {
		fprintf( stderr, "fail\n" );
		db.AddKey( key, data );
		fprintf( stderr, "Finding key '%s'... ", key );
		if(	db.GetData( key, data, 128 ) == true )	{
			fprintf( stdout, "[%s]\n", data );
		}
	}

	db.Close();
	fprintf( stderr, "DB %s/%s closed\n", dir, fn );
	return 0;

}

