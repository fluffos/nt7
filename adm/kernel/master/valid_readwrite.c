// This program is a part of NT MudLIB

/*
名称：
        valid_read - 检查一个人是否有权读取一个档案。
语法：
        int valid_read( string file, object user, string func );

        整数 valid_read( 字串 档案, 物件 使用者, 字串 函式 );
用法：
        每次当一个物件尝试读取档案时，驱动程式会呼叫主宰物件的 valid_read()
        以检查是否允许读取。此函式的参数为档案名称、尝试读取此档的物件、呼
        叫的函式名称。如果 valid_read() 传回非零值，则准许读取。
参考：
        valid_write
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_read: read privileges; called exactly the same as valid_write()
int valid_read(string file, mixed user, string func)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_read(file, user, func);

        return 1;
}

/*
名称：
        valid_write - 检查一个物件是否有权写入一个档案。
语法：
        int valid_write( string file, object ob, string func );

        整数 valid_write( 字串 档案, 物件 物件, 字串 函式 );
用法：
        每次当一个物件尝试写入档案时，驱动程式会呼叫主宰物件中的
        valid_write() 以检查是否允许写入。此函式的参数为档案名称、尝试写入
        此档的物件、呼叫的函式名称〈通常是被使用的外部函式〉。如果
        valid_write() 传回非零值，则准许写入。
参考：
        valid_read
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_write: write privileges; called with the file name, the object
// initiating the call, and the function by which they called it.
int valid_write(string file, mixed user, string func)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_write(file, user, func);

        return 0;
}
