// This program is a part of NT MudLIB

/*
名称：

       valid_hide - 允许或禁止一个物件具有匿踪 (hide) 及看到匿踪物件的能力。
语法：
        int valid_hide( object ob );

        整数 valid_hide( 物件 物件 );
用法：
        在主宰物件中 (master.c) 加上 valid_hide 可以让物件具有自我匿踪和看
        到其他匿踪物件的能力。当一个物件使用 set_hide() 函式以进入匿踪状态
        时，此物件就当成 valid_hide() 的唯一参数呼叫此函式。允许此物件匿踪
        时应传回 1，反之则传回 0。当一个物件想看到匿踪状态的物件时，也以同
        样的方式呼叫此函式。
参考：
        set_hide
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_hide: controls the use of the set_hide() efun, to hide objects or see hidden objects
int valid_hide(object who)
{
        return 1;
}

/*
int valid_hide(object ob)
{
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n this_player():%O\n this_player(1):%O\n",call_stack(1),this_player(),this_player(1)));
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n\n",find_player("lonely")));
        //if( call_stack(1)[<1]==this_object() ) return 1;
        if( this_player() && wizardp(this_player()) ) return 1;
        return 0;
}
*/