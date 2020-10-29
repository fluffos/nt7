// This program is a part of NT MudLIB

/*
名称：
        valid_bind - 判断一个指定的函式指标 (function pointer) 是否能结合
                     (bind) 到一个物件上。
语法：
        int valid_bind( object doer, object owner, object victim );

        整数 valid_bind( 物件 作用者, 物件 拥有者, 物件 受害者 );
用法：
        当 doer 尝试使用 bind() 外部函式结合 owner 对 victim 物件的函式指
        标，会呼叫此函式。如果此函式传回 0，就禁止结合。
参考：
        bind
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

int valid_bind(object binder, object old_owner, object new_owner)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_bind(binder, old_owner, new_owner);

        return 1;
}