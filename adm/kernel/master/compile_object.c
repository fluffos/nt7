// This program is a part of NT MudLIB

// compile_object: This is used for loading MudOS "virtual" objects.
// It should return the object the mudlib wishes to associate with the
// filename named by 'file'.  It should return 0 if no object is to be
// associated.
/*
名称：
        compile_object - 提供虚拟物件 (virtual object) 功能的 mudlib 介面。
语法：
        object compile_object( string pathname );

        物件 compile_object( 字串 路径名 );
用法：
        当 mudlib 指示驱动程式载入一个不存在于记忆体中的档案，驱动程式会呼
        叫 compile_object 函式。举例来说，如果 mudlib 呼叫
        call_other("/obj/file.r", "some_function") 或 new("/obj/file.r") 时
        ，记忆体中没有叫做 /obj/file.r.c 的东西，驱动程式就呼叫主宰物件
         (master object) 的 compile_object("/obj/file.r")。如果 mudlib 不希
        望连结 (associate) /obj/file.r 档案，compile_object() 将传回 0。如
        果 mudlib 愿意，就要传回 /obj/file.r 这个物件。在 compile_object()
        连结一个档案名称和物件之后，对驱动程式而言，就如同游戏中存在
        file.r.c 这个档案，而载入此物件时产生的就是 compile_object() 传回的
        物件。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.20.    v22 版
*/

varargs mixed compile_object(string file, int cloning)
{
        object daemon;

        if( daemon = find_object(VIRTUAL_D) )
                return daemon->compile_object(file, cloning);
        else
                return 0;
}