#include "mgt.h"

void load( char *prefix, char *key )
{
	CUMGT mgt;
	if( mgt.Load( prefix ) == false )
	{
		fprintf( stderr, "Error: fail to load %s\n", prefix );
		return;
	}
	fprintf( stderr, "Record: %d\n", mgt.GetNumRecord() );

	CUMGTInfo info;
	if( mgt.GetInfo( key, info ) == false )
	{
		fprintf( stderr, "No key: %s\n", key );
	}
	else
	{
		CUString ret;
		if(  mgt.GetContent( info, ret ) == false )
		{
			fprintf( stderr, "Fail to get content\n" );
		}
		else
		{
			fprintf( stdout, "%s", ret.GetStr() );
		}
	}
}


int main( int argc, char *argv[] )
{
	if( argc != 3 )
	{
		fprintf( stderr, "mgt prefix docno\n" );
		return 1;
	}

	load( argv[1], argv[2] );

	return 0;
}

