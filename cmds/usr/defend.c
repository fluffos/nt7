// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if (! arg || arg == "")
                return notify_fail("你要向谁领取保卫门派任务？\n");
        
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("这里没有这个人，你怎么领任务？\n");

        if (! living(ob))
                return notify_fail("你还是等" + ob->name() +
                                   "醒了再说吧！\n");

        if (me->is_fighting())
                return notify_fail("专心打你的架！\n");

        if (me->is_busy())
                return notify_fail("你还是有空了再和" + ob->name() +
                                   "谈这些问题吧！\n");

        if (ob->is_fighting())
                return notify_fail("你还是等" + ob->name() +
                                   "打完架再说吧！\n");

        if (ob->is_busy())
                return notify_fail(ob->name() +
                                   "正忙着呢，没功夫理你。\n");

        notify_fail(ob->name() + "望着你呵呵的傻笑。\n");
        return ob->ask_defend(me);
}

int help(object me)
{
        write(@HELP
指令格式 : defend  这个指令可以用来向你的门派的掌门或世家长辈
领取任务。
HELP );
        return 1;
}