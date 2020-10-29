// copyskill.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

protected int copy_stats(object me, object ob, string stats);
int help();

int main(object me, string arg)
{
        object ob;
        object tob;
        string stats, who, target;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
        {
                help();
                return 1;
        }

        if (sscanf(arg, "%s from %s to %s", stats, who, target) == 3)
        {
                if (! objectp(tob = present(target, environment(me))))
                        return notify_fail("你眼前没有 " + target + " 这个物件。\n");
        } else
                tob = me;

        if (wiz_level(me) <= wiz_level(tob) && me != tob)
                return notify_fail("你只能给权限比自己低的人复制状态。\n");

        if (who == "me")
                ob = me;
        else
        if (! objectp(ob = present(who, environment(me))))
                return notify_fail("你眼前没有 " + who + " 这个物件。\n");

        if (! is_root(me) && playerp(tob) && ! wizardp(tob))
                return notify_fail("只有天神才能给普通玩家复制状态。\n");

        if (ob == tob)
                return notify_fail("不需要复制吧。\n");

        if (me != tob)
                log_file("static/copystats", sprintf("%s %s copy %s(%s)'s stats to %s(%s).\n",
                                                     log_time(), log_id(me),
                                                     ob->name(1),query("id", ob),
                                                     tob->name(1), tob->query("id")));
        copy_stats(tob, ob, stats);
        message_vision(HIM + me->name(1) + HIM "口中念念有词，只见一道红光笼罩了$N"
                       HIM "和$n" HIM "。\n" NOR, tob, ob);
        return 1;
}

protected int copy_stats(object me, object ob, string stats)
{
        mapping your;
        mapping my;

        your = ob->query_entire_dbase();
        my = me->query_entire_dbase();
        
        if (! undefinedp(your[stats]))
                my[stats] = your[stats];
 
        return 1;
}

int help()
{
        write(@TEXT
指令格式：copystats <stats> from <对象> [to <目的对象>]

这个指令让你复制对象的状态。

该命令在可以被授权使用的信息包括：me、wizard、all。
TEXT );
        return 1 ;
}
