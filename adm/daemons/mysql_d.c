// This program is a part of NT mudlib


mapping mysql;
 
#define DEFAULT_HOSTNAME 	"localhost"
#define DEFAULT_DATABASE        "mud"
#define DEFAULT_USERNAME        "xkx"
 
//#define MSG(x, y)               CHANNEL_D->channel_broadcast("nch", "MYSQL_D["+x+"]: "+y)
#define MSG(x, y)

varargs mixed exec(int handle, string sql);

// 建立 MYSQL 连线
varargs mixed connect(string hostname, string database, string username)
{
	mixed handle;
	
	if( undefinedp(hostname) )
		hostname = DEFAULT_HOSTNAME;

	if( undefinedp(database) )
		database = DEFAULT_DATABASE;

	if( undefinedp(username) )
		username = DEFAULT_USERNAME;

	handle = db_connect(hostname, database, username, 0);
	
	if( intp(handle) )
	{
		mysql[handle] = ({ hostname, database, username });
		MSG(handle, "connect to "+hostname+"(database:"+database+", user:"+username+") successfully");
                //exec(handle, "SET CHARACTER SET BIG5");
	}
	else
		MSG(0, handle); 
		
	return handle;
}
 
// 关闭 MYSQL 连线
varargs int close(int handle)
{
	if( undefinedp(handle) )
	{
		foreach(handle, string *data in mysql)
		{
			MSG(handle, "close connection");
			db_close(handle);
		}
		mysql = allocate_mapping(0);
	}
	else
	{
		MSG(handle, "close connection");
		map_delete(mysql, handle);
		return db_close(handle);
	}
	
	return 1;
}


// 执行 SQL 指令
varargs mixed exec(int handle, string sql)
{
	mixed value;
	
	value = db_exec(handle, sql);
	
	//if( !value )
	//	MSG(handle, "exec \""+sql+"\"");
	//else
	if( value )
		MSG(handle, "exec "+value);
	
	return value;
}

string status()
{
	return db_status();
}

int rollback(int handle)
{
	return db_rollback(handle);
}

mixed fetch(int handle, int set)
{
	return db_fetch(handle, set);
}

int commit(int handle)
{
	return db_commit(handle);
}

void create()
{
	mysql = allocate_mapping(0);
}

void updatetime(int handle, string table)
{
        exec(handle, "UPDATE `updated` SET `time`=NOW() WHERE `table`='"+table+"'");
}

int remove()
{
	close();
}
string query_name()
{
	return "MYSQL 资料库系统(MYSQL_D)";
}
