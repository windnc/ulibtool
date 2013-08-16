#include "mgt.h"

void dump( char *mgt_prefix, char *flist_fn, char *out_dn )
{
	CUMGT mgt;
	if( mgt.Load( mgt_prefix ) == false )
	{
		fprintf( stderr, "Error: fail to load %s\n", mgt_prefix );
		return;
	}

	fprintf( stderr, "record: %d\n", mgt.GetNumRecord() );

	/*
	CUMGTInfo info;
	if( mgt.GetInfo( "hello", info ) == false )
	{
		fprintf( stderr, "No key\n" );
	}
	else
	{
		fprintf( stderr, "%ld ~ %ld\n", info.start, info.end );
	}


	CUStringList list = mgt.GetKeyList();
	for( int i=0; i<(int)list.GetSize(); i++ )
	{
		fprintf( stderr, "[%d] %s\n", i, list.GetAt(i) );
	}
	*/


}


int main( int argc, char *argv[] )
{
	if( argc != 4 )
	{
		fprintf( stderr, "Usage: %s [mgt-prefix] [flist-fn] [out-dir]\n", argv[0] );
	}

	dump( argv[1], argv[2], argv[3] );

	return 0;
}

