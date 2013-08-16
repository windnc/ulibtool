#ifndef __MGT__
#define __MGT__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ulib.h"


class CUMGTInfo {
public:
	unsigned long start;
	unsigned long end;
};

class CUMGT {
public:
	CUMGT();
	~CUMGT();
public:

	bool Load( char *prefix );
	bool IsLoaded();
	void Close();
	int GetNumRecord() {	return info_map.size(); }
	CUStringList GetKeyList();
	bool HaveKey( char *key );
	bool GetInfo( char *key, CUMGTInfo &info );
	bool GetInfo( char *key, unsigned long &start, unsigned long &end );
	bool GetContent( char *key, CUString &ret );
	bool GetContent( CUMGTInfo info, CUString &ret );
	bool GetContent( char *key, void *ret );
	bool GetContent( CUMGTInfo info, void *ret );

	bool Create( char *prefix );
	bool Insert( char *key, char *content );
	bool Insert( char *key, char *content, int len );
//	bool Delete( char *key );

	map<string, CUMGTInfo> info_map;

private:
	CUTextFile key_file;
	CUTextFile content_file;

};

#endif

