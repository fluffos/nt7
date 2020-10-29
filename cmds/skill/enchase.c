// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item, tessera;
        object obj, dest;

        if (! arg)
                return notify_fail("你要往什么道具上镶嵌物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if (sscanf(arg, "%s with %s", item, tessera) != 2 &&
            sscanf(arg, "%s in %s", tessera, item) != 2)
                return notify_fail("你要往这上面镶嵌什么物品？\n");

        if (! objectp(obj = present(tessera, me)))
                return notify_fail("你身上没有这样东西可以用来镶嵌。\n");

        if (! objectp(dest = present(item, me)))
                return notify_fail("你身上没有这样道具。\n");

        if( query("no_identify", obj) )
                return notify_fail("此物品还没有签定。\n");

        if( query("qianghua/level", dest) && !query("can_be_qiling", obj) )
                return notify_fail("此物品已经强化过，无法再镶嵌物品。\n");

        notify_fail("你无法把" + obj->name() + "镶嵌到" + dest->name() + "上。\n");

        //return dest->do_enchase(me, obj);
        return ITEM_D->do_enchase(me, dest, obj);

}

int help(object me)
{
        write(@HELP
指令格式 : enchase <特殊物品> in <道具>
           enchase <道具> with <特殊物品>

这个指令可以让你将某样特殊物品镶嵌到另外一种道具上，使得道具
具有特殊的能力。
HELP
        );
        return 1;
}
