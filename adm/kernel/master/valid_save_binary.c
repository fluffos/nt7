// This program is a part of NT MudLIB

/*
名称：
        valid_save_binary - 控制一个物件是否可以储存它已载入的程式。
语法：
        int valid_save_binary( string file );

        整数 valid_save_binary( 字串 file );
用法：
        只有启动 BINARIES 时有效。

        驱动程式编译时，如果定义了 ALWAYS_SAVE_BINARIES；或是一个物件中使
        用了 // #pragma save_binary，就会以程式的档案名称作为参数呼叫
        valid_save_binary。如果 valid_save_binary 传回 1，此程式会储存到硬
        碟中以加快重新载入的时间。反之则不储存，下次重新载入时会如同往常一
        样重新编译一次。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_save_binary: controls whether an object can save a binary
//   image of itself to the specified "save binaries directory"
//   (see config file)
int valid_save_binary(string filename)
{
        return 1;
}
