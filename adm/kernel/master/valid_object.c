// This program is a part of NT MudLIB

/*
名称：
        valid_object - 让你能控制是否要载入某个物件。
语法：
        int valid_object( object obj );

        整数 valid_object( 物件 物件 );
用法：
        载入一个物件之后，驱动程式会以新创造的物件为参数，呼叫主宰物件
        (master object) 的 valid_object()。如果 valid_object() 存在，并传
        回 0，则会摧毁此物件并使载入物件的外部函式 (efun) 产生错误输出。如
        果此函式不存在或是传回 1，则载入物件的过程就跟平常一样。此函式呼叫
        时，该物件还没有机会执行任何程式码，包括 create()在内，所以该物件
        除了 file_name(obj) 之外，没有多少东西有效。
参考：
        valid_override
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/
// valid_object: controls whether an object loaded by the driver should exist
int valid_object(object ob)
{
        return (!clonep(ob)) || inherits(F_MOVE, ob);
}