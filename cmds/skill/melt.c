#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;

        if (! arg)
                return notify_fail("你要溶化什么道具的凹槽物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上没有这样道具。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + CYN "的装备再说！\n");

        if( !ob->is_item_make() && !query("unique", ob) )
                return notify_fail("这类物品无须清理凹槽。\n");

        if( !wizardp(me) && (ob->is_item_make() && ob->item_owner() != query("id", me)) )
                return notify_fail("这不是你的物品。\n");

        if( !query("armor_type", ob) && !query("skill_type", ob) )
                return notify_fail("这类物品无须清理凹槽。\n");

        if( !query("enchase/flute", ob) )
                return notify_fail("这还没有开槽过了呢。\n");

        if( !query("enchase/used", ob) )
                return notify_fail("这上面没有镶嵌过东西。\n");

        notify_fail(ob->name() + "的凹槽物品没有办法被熔炼。\n");

        return ob->do_wash(me);
}

int help(object me)
{
write(@HELP
指令格式 : melt <物品名称>

这个指令可以让你运用内力将道具凹槽里的物品溶化掉。
HELP
    );
    return 1;
}
