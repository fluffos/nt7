// This program is a part of NT MudLIB
// rideto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        object riding, env;
        string where;
        string file;

        if( !arg )
        {
                MAP_D->show_trans(me);
                return 1;
        }
                
        if (me->over_encumbranced())
                return notify_fail("你的负荷过重，动弹不得。\n");

        if (me->query_encumbrance() < 0)
                return notify_fail("你的负荷出现故障，动弹不得。\n");

        if( query_temp("sleeped", me) )
                return notify_fail("你现在正躺着呢。\n");

        if (me->is_in_prison())
                return notify_fail("你正在做牢呢，你想干什么？！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在战斗！\n");

        if( me->is_ghost() )
                return notify_fail("你还是等还阳后再说吧。\n");

        if( me->is_busy() || (query("doing", me) && query("doing", me) != "trigger") )
                return notify_fail("你的动作还没有完成，不能移动。\n");

        // 帐篷中不能rideto
        env = environment(me);
        if( objectp(env) )
        {
                if( base_name(env) == "/clone/fam/item/zhangpeng" || 
                        base_name(env) == "/clone/fam/item/zhangpeng2" )
                {
                        return notify_fail("此处不能骑马！\n");
                }
        }

        if( query("no_rideto", env) || query("no_flyto", env) )
                return notify_fail("这里无法骑马穿梭。\n");
               
        if( query("no_magic", env) || query("maze", env) )
                return notify_fail("你发现这里无法骑马穿梭。\n");

        //if (me->query_condition("killer"))
        //        return notify_fail("你有命案在身呢，你还是小心为妙，不宜在官道上肆无忌惮行走！\n");
/*
        if( !query("outdoors", environment(me)) )
                return notify_fail("在房间里不能骑马穿梭。\n");
*/
        if( !objectp(riding=query_temp("is_riding", me)) )
        {
                file = "/data/warcraft/"+query("id",me)+".c";
                if( file_size(file) < 0 )
                        return notify_fail("你还没有坐骑！\n");
                call_other(file, "???");
                riding = find_object(file);

                if( !riding || !riding->receive_whistle(me, 1) )
                        return notify_fail("你还没有坐骑！\n");
        }
        
        if( !objectp(present(query("id", riding), me)) )
                return notify_fail("你的坐骑不在你身边！\n");

        if( objectp(riding=query_temp("is_riding", me)) )
        {           
                MAP_D->move_to(me, arg);
                return 1;
        }
        
        //return notify_fail("你还是先找匹坐骑再说吧。\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : rideto <地点>

这个指令可以让你骑马到指定地点，如果指定不带参数可以
参看你所能到的地方。

HELP );
        return 1;
}
