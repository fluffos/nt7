// increase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, item;

        if (! arg)
                return notify_fail("你要改造什么物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("你身上没有这样道具。\n");

        if (! objectp(obj = present("increase stone", me)))
                return notify_fail("你身上没有改造石。\n");

        notify_fail(item->name() + "没有办法被改造。\n");

        return item->do_increase(me, obj);
}

int help(object me)
{
write(@HELP
指令格式 : increase <物品名称>

这个指令可以让你改造道具，以锻炼那种道具或是发挥它的威力，每
次消耗改造石一块。

HELP
    );
    return 1;
}