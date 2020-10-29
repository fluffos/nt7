// This program is a part of NT MudLIB

/*

        valid_shadow - 控制哪些物件可以被投影 (shadow)。
语法：
        int valid_shadow( object ob );

        整数 valid_shadow( 物件 物件 );
用法：
        当一个物件尝试投影 ob 时〈使用 shadow() 外部函式 (efun)〉，会呼叫
        主宰物件中的 valid_shadow() 函式。一个物件应该作为此函式的参数。此
        物件是 previous_object() 尝试投影的物件。如果不准投影，
        valid_shadow() 应传回 0，导致 shadow() 呼叫失败并传回 0。如果
        valid_shadow() 传回 1，则允许投影。
参考：
        shadow, query_shadowing
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_shadow: controls whether an object may be shadowed or not
int valid_shadow(object ob)
{
        object pre;

        pre = previous_object();
        if( geteuid(pre) == ROOT_UID ||
            sscanf(file_name(pre), "/shadow/%*s") ) {
                return 1;
        }

        log_file("shadow", sprintf("%O try to shadow %O failed.\n", pre, ob));
        return 0;
}
