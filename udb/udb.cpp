#include "udb.h"

CUDB::CUDB()
{
	isOpened = false;
	db = NULL;
	env = NULL;
	txn = NULL;
}

CUDB::~CUDB()
{
}

bool CUDB::Open( char *dir, char *fn )
{
	if( IsOpened() == true )	{
		Close();
	}

	int ret = 0;
	u_int32_t flag = 0;

	// open env
	ret = db_env_create( &env, 0 );
	if( ret != 0 )	{
		return false;
	}
	flag = DB_CREATE | DB_INIT_TXN | DB_INIT_LOCK | DB_INIT_MPOOL;
	ret = env->open( env, dir, flag, 0 );
	if( ret != 0 )	{
		return false;
	}

	// open db
	db_create( &db, env, 0);
	if( ret != 0 )	{
		return false;
	}
	
	u_int32_t flags = DB_CREATE | DB_AUTO_COMMIT;
	ret = db->open( db, NULL, dir, NULL, DB_BTREE, flags, 0 );
	if( ret != 0 )	{
		return false;
	}

	// txn
	ret = env->txn_begin( env, NULL, &txn, 0 );
	if( ret != 0 )	{
		return false;
	}

	isOpened = true;
	return true;
}


bool CUDB::AddKey( char *key, char *data )
{
	DBT _key;
	memset( &_key, 0, sizeof(DBT) );
	_key.data = (void *)key;
	_key.size = strlen( key ) + 1;

	DBT _data;
	memset( &_data, 0, sizeof(DBT) );
	_data.data = (void *)data;
	_data.size = strlen( data ) + 1;

	int ret = db->put( db, txn, &_key, &_data, DB_NOOVERWRITE);
	if( ret != 0 )	{
		fprintf( stderr, "%s\n", db_strerror( ret ) );
		return false;
	}

	return true;
}


bool CUDB::GetData( char *key, char *data, int size )
{
	if( IsOpened() == false )	return false;

	DBT _key;
	memset( &_key, 0, sizeof(DBT) );
	_key.data = (void *)key;
	_key.size = strlen( key ) + 1;

	DBT _data;
	memset( &_data, 0, sizeof(DBT) );
	_data.data = (void *)data;
	_data.ulen = size;
	_data.size = DB_DBT_USERMEM;

	int ret = db->get( db, txn, &_key, &_data, 0);
	if( ret != 0 )	{
		//fprintf( stderr, "%s\n", db_strerror( ret ) );
		return false;
	}

	data[_data.size] = 2;
	return true;
}


bool CUDB::IsOpened()
{
	return isOpened;
}


void CUDB::Close()
{
	if( IsOpened() == false )	return;

	txn->commit( txn, 0 );

	if( db )	db->close( db, 0 );
	if( env )	env->close( env, 0 );

	isOpened = false;
}


