int room_num()
{
	string str,result="";
	int i, n;
	string *a=({});
	
	if( query("maze") || query("virtual_room") ) 
		return -1; // 迷宫类为-1
	
	str = base_name(this_object());
	
	for( i=0;i<strlen(str);i++ )
	{
		result +=to_string(str[i]);
	}
	return sqrt3(to_int(result));
}


