// This program is a part of NT MudLIB

/*
名称：
        valid_override - 控制 efun:: 的用途。
语法：
        int valid_override( string file, string efun_name, string mainfile );

        整数 valid_override( 字串 档案, 字串 外部函式名, 字串 主档案 );
用法：
        file 是该呼叫实际上所处的档案；mainfile 是欲编译的档案〈因为
        #include 的关系，两者可能会不同〉。

        在主宰物件 (master.c) 中加上 valid_override() 可以控制 efun:: 这种
        前置语法 (prefix) 的用途。每次当驱动程式尝试编译前面加上 efun:: 的
        函式时，会呼叫主宰物件中的 valid_override()。如果 valid_override()
        传回 0，则编译失败。所以一些禁止由 efun:: 前置语法规避原作用的外部
        函式，valid_override() 可以提供一个方法修改它们的作用。

        如果您希望使用原来 3.1.2  版 efun:: 的作用，只需要在主宰物件
        master.c 中加上下面这行：

        int valid_override(string file, string efun) { return 1; }

        底下是一个限制较多的 valid_override() 范例：
        〈译按：本范例与 21 版并无不同，但是目前已多了 mainfile 参数〉

        int valid_override( string file, string name )
        {
                if (file == "/adm/kernel/simul_efun") {
                        return 1;
                }

                if (name == "destruct")
                        return 0;
                if (name == "shutdown")
                        return 0;
                if (name == "snoop")
                        return 0;
                if (name == "exec")
                        return 0;

                return 1;
        }
参考：
        valid_object, function_exists
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版

*/
// valid_override: controls which simul_efuns may be overridden with
// efun:: prefix and which may not.  This function is only called at
// object compile-time
int valid_override( string file, string name )
{
        // simul_efun can override any simul_efun by Annihilator
        if( file == SIMUL_EFUN_OB || file == MASTER_OB )
                return 1;

        // Must use the move() defined in F_MOVE.
        if( (name == "move_object") && file != F_MOVE && file != F_COMMAND )
                return 0;

        if( (name == "destruct") && ! sscanf(file, "/adm/kernel/simul_efun/%s", file) )
                return 0;

        //  may also wish to protect destruct, shutdown, snoop, and exec.
        return 1;
}

/*
int valid_override(string file, string name, string mainfile)
{

        if( file[0..24] == SIMUL_EFUN_OB[0..24] ) return 1;

        switch(name)
        {
                case "memory_summary":
                case "destruct"        :
                case "shutdown"        :
                case "exec"        :        return 0;
                default                :        return 1;
        }
}
*/
