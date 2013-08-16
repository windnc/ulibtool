#include "mgt.h"

void create()
{
	char *prefix = "tiny";

	CUMGT mgt;
	if( mgt.Create( prefix ) == false )
	{
		fprintf( stderr, "Error: fail to create %s\n", prefix );
		return;
	}

	if( mgt.Insert( "hello", "this is test1." ) == false ) {  }
	if( mgt.Insert( "hello", "this is test2." ) == false ) {  }
	if( mgt.Insert( "hell ", "this is test2." ) == false ) {  }


	mgt.Close();
}


void load()
{
	char *prefix = "tiny";

	CUMGT mgt;
	if( mgt.Load( prefix ) == false )
	{
		fprintf( stderr, "Error: fail to load %s\n", prefix );
		return;
	}

	fprintf( stderr, "record: %d\n", mgt.GetNumRecord() );

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


}


int main()
{

	create();
	load();

	return 0;
}

