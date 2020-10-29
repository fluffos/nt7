// stop.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int cost, i = 0;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要命令谁？\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要命令谁？\n");

        if( query_temp("owner", ob) != query("id", me) )
                return notify_fail("人家不会听你的话的。\n");

        if (! ob->is_fighting())
                return notify_fail(ob->name() + "现在并没有和别人搏斗。\n");

        if( query("can_speak", ob) )
                message_vision("$N大喝一声道：“" + ob->name() + "，住手！”\n",
                               me);
        else
                message_vision("只见$N冲着$n口中一声呼哨，$n向后一窜，不咬了！\n",
                               me, ob);

        ob->force_me("halt");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : stop <对象>

此指令可用于让你的跟随者或是驯养的动物停止攻击他人。
HELP );
        return 1;
}