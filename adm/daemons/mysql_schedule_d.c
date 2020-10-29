#define MYSQL_D          "/adm/daemons/mysql_d"

// Called by HISTORY_D
void refresh_history()
{
        string *game_history;
	mixed handle;
	string sql = "";
	
	if( !intp(handle = MYSQL_D->connect()) )
		return;
	
	MYSQL_D->exec(handle, "DELETE FROM history");
	
	sql = "INSERT INTO `history` VALUES";
	
	game_history = HISTORY_D->query_history();
	
	for(int i=0;i<sizeof(game_history);i+=3)
		sql += "('"+TIME_D->replace_ctime(game_history[i])+"','"+replace_string(game_history[i+1],"'", "\\'")+"','"+replace_string(game_history[i+2],"'", "\\'")+"'),";

	sql = remove_ansi(sql[0..<2]);

	MYSQL_D->exec(handle, sql);
	MYSQL_D->updatetime(handle, "history");
	MYSQL_D->close(handle);
}

int mudlist_sort(mapping mudlist, string mud1, string mud2)
{
	string mud1_chinese = mudlist[mud1]["MUD_CHINESE_NAME"];
	string mud2_chinese = mudlist[mud2]["MUD_CHINESE_NAME"];
	string mud1_english = mudlist[mud1]["MUD_ENGLISH_NAME"];
	string mud2_english = mudlist[mud2]["MUD_ENGLISH_NAME"];

	if( sizeof(mud1_chinese) != sizeof(mud2_chinese) )
		return sizeof(mud1_chinese) > sizeof(mud2_chinese) ? 1 : -1;
	
	return strcmp(mud1_chinese || mud1_english, mud2_chinese || mud2_english);
}

// Called by TIME_D
void refresh_mudlist()
{
	mixed handle;
	string ipport;
	string ip;
	int port;
	int status;
	int users;
	string lasttime;
	string sql = "";
	mapping muds;
	mapping data;
	string *mudnamesort;
	
	if( !intp(handle = MYSQL_D->connect()) )
		return;
	
	muds = MUDLIST_D->query_mudlist();
	
	MYSQL_D->exec(handle, "DELETE FROM mudlist");
	
	sql = "INSERT INTO `mudlist` VALUES";
	
	mudnamesort = sort_array(keys(muds)-({0}), (: mudlist_sort($(muds), $1, $2) :)) ;
		
	foreach(ipport in mudnamesort)
	{
		data  = muds[ipport];

		if( !stringp(ipport) || !mapp(data) ) continue;
		
		sscanf(ipport, "%s %d", ip, port);
		
		if( data["CONNECT_FAILED_TIMES"] > 0 )
			status = 0;
		else
			status = 1;
		
		if( data["USERS"] > 0 )
			users = data["USERS"];
		else if( !data["USERS_COUNT_PARSE"] )
			users = -1;
		else
			users = 0;

		if( data["LAST_CONTACT_TIME"] )
			lasttime = TIME_D->replace_ctime(data["LAST_CONTACT_TIME"]);
		else
			lasttime = "";
			
		sql += "('"+
			(data["MUD_CHINESE_NAME"]||"--未知名称--")+"','"+
			(data["MUD_ENGLISH_NAME"]||"--Unknown--")+"','"+
			ip+"',"+
			port+","+
			status+","+
			users+",'"+
			lasttime+"'),";
		
	}
	
	sql = remove_ansi(sql[0..<2]);
	MYSQL_D->exec(handle, sql);
	MYSQL_D->updatetime(handle, "mudlist");
	MYSQL_D->close(handle);
}

void set_captcha(string id, string code)
{
	mixed handle;
	string sql;
	
	if( !intp(handle = MYSQL_D->connect()) )
		return;
	
	MYSQL_D->exec(handle, "DELETE FROM captcha WHERE id='"+id+"'");
	
        sql = "INSERT INTO captcha (`id`,`value`) VALUES ('"+id+"','"+code+"')";
	
	MYSQL_D->exec(handle, sql);
	MYSQL_D->close(handle);
}

void delete_captcha(string id)
{
	mixed handle;
	
	if( !intp(handle = MYSQL_D->connect()) )
		return;
	
	MYSQL_D->exec(handle, "DELETE FROM captcha WHERE id='"+id+"'");
	
	MYSQL_D->close(handle);
}


void create()
{
        seteuid(getuid()); 
}
string query_name()
{
	return "MYSQL 排程系统(MYSQL_SCHEDULE_D)";
}
