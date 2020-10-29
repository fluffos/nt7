// This program is a part of NT MudLIB

/*
名称：
        valid_link - 控制 link 外部函式的用途。
语法：
        int valid_link( string from, string to );

        整数 valid_link( 字串 from, 字串 to );
用法：
        驱动程式回从 link(from, to) 外部函式里面呼叫主宰物件 (master
        object) 里面的 valid_link(from, to) 函式。如果 valid_link() 传回 0
        ，则 link() 的动作失败。如果传回 1，还需要以同样的参数呼叫
        rename() 成功。
参考：
        link
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版

*/

// valid_link: controls use of the link() efun for creating hard links between paths
int valid_link(string original, string reference)
{
        return 0;
}