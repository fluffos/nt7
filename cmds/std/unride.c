// Filename : /cmds/std/unride.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
        object ob, follower;

        if( !objectp(ob=query_temp("is_riding", me)) )
                return notify_fail("你下什么下！根本就没座骑！\n");

        message_vision("$N从$n上飞身跳下。\n", me, ob);
        ob->move( environment(me) );
        ob->delele_temp("is_rided_by");
        delete_temp("is_riding", me);
        // 让所有的人也下马
        if (objectp(follower = query_temp("is_rided_follow", ob)))
        {
                delete_temp("is_riding_follow", follower);
                delete_temp("is_rided_follow", ob);
                //message_vision("$N强行要求所有人下马。\n", me);
                message_vision("$N从$n上飞身跳下。\n", follower, ob);
        }
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : unride | xia
 
这个指令可以让你从骑着的已驯养的动物上跳下来。
 
HELP );
    return 1;
}
