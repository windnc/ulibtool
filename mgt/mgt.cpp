#include "mgt.h"

CUMGT::CUMGT()
{
}

CUMGT::~CUMGT()
{
	Close();
}

bool CUMGT::IsLoaded()
{
	if( key_file.IsOpen() == false )	return false;
	if( content_file.IsOpen() == false )	return false;
	return true;
}


void CUMGT::Close()
{
	if( key_file.IsOpen() == true )	key_file.CloseFile();
	if( content_file.IsOpen() == true )	content_file.CloseFile();
}

bool CUMGT::Create( char *prefix )
{
	Close();

	char buf[1024];
	sprintf( buf, "%s.mgt-key", prefix );
	if( key_file.OpenFile( buf, "w" ) == false )
	{
		return false;
	}

	sprintf( buf, "%s.mgt-content", prefix );
	if( content_file.OpenFile( buf, "wb" ) == false )
	{
		return false;
	}

	return true;
}

bool CUMGT::Load( char *prefix )
{
	Close();
	char buf[1024];
	sprintf( buf, "%s.mgt-key", prefix );
	if( key_file.OpenFile( buf, "r" ) == false )
	{
		return false;
	}

	sprintf( buf, "%s.mgt-content", prefix );
	if( content_file.OpenFile( buf, "r" ) == false )
	{
		return false;
	}

	info_map.clear();
	while( true )
	{
		CUString line;
		if( key_file.ReadLine( line ) == false ) break;
		CUStringList list( line, "\t" );
		if( list.GetSize() != 3 )	continue;

		if( info_map.find( list.GetAt(0) ) != info_map.end() )
		{
			fprintf( stderr, "Error: Duplicated key: %s\n", list.GetAt(0) );
			return false;
		}


		CUMGTInfo info;
		info.start = atol( list.GetAt(1) );
		info.end   = atol( list.GetAt(2) );
		info_map[ list.GetAt(0) ] = info;
	}

	return true;
}


bool CUMGT::Insert( char *key, char *content )
{
	if( IsLoaded() == false )	return false;
	map<string, CUMGTInfo>::iterator itr = info_map.find( key );
	if( itr != info_map.end() )	return false;

	CUMGTInfo info;

	info.start = ftell( content_file.GetFP() );
	fprintf( content_file.GetFP(), "%s\n", content );
	info.end = ftell( content_file.GetFP() );

	info_map[ key ] = info;

	fprintf( key_file.GetFP(), "%s\t%ld\t%ld\n", key, info.start, info.end );
	return true;
}

bool CUMGT::Insert( char *key, char *content, int len )
{
	if( IsLoaded() == false )	return false;
	map<string, CUMGTInfo>::iterator itr = info_map.find( key );
	if( itr != info_map.end() )	return false;

	CUMGTInfo info;

	info.start = ftell( content_file.GetFP() );
	fwrite( content, 1, len, content_file.GetFP()  );
	fprintf( content_file.GetFP(), "\n" );
	info.end = ftell( content_file.GetFP() );

	info_map[ key ] = info;

	fprintf( key_file.GetFP(), "%s\t%ld\t%ld\n", key, info.start, info.end );
	return true;
}

CUStringList CUMGT::GetKeyList()
{
	CUStringList list;
	map<string,CUMGTInfo>::iterator itr = info_map.begin();
	while( itr != info_map.end() )
	{
		list.PushBack( itr->first.c_str() );
		itr++;
	}
	return list;

}



bool CUMGT::GetInfo( char *key, CUMGTInfo &info )
{
	map<string, CUMGTInfo>::iterator itr = info_map.find( key );
	if( itr == info_map.end() )	return false;

	info = itr->second;
	return true;
}


bool CUMGT::GetContent( CUMGTInfo info, CUString &ret )
{
	if( IsLoaded() == false )	return false;

	int len = info.end - info.start;
	if( len < 0 )	return false;

	char *buf = new char[len+1];
	fseek( content_file.GetFP(), info.start, SEEK_SET );
	fread( buf, len, sizeof(char),  content_file.GetFP() );
	buf[len] = '\0';

	ret = buf;
	delete buf;

	return true;
}


bool CUMGT::GetContent( CUMGTInfo info, void *ret )
{
	if( IsLoaded() == false )	return false;

	int len = info.end - info.start;
	if( len < 0 )	return false;

	fseek( content_file.GetFP(), info.start, SEEK_SET );
	fread( ret, len, sizeof(char),  content_file.GetFP() );

	return true;
}
bool CUMGT::GetContent( char *key, CUString &ret )
{
	CUMGTInfo info;
	if( GetInfo(key, info ) == false )	return false;

	return GetContent( info, ret );
}


bool CUMGT::GetContent( char *key, void *ret )
{
	CUMGTInfo info;
	if( GetInfo(key, info ) == false )	return false;

	return GetContent( info, ret );
}

