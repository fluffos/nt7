// forging.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, item;

        if( !arg )
                return notify_fail("你要锻造什么物品？\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if( me->is_fighting() )
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if( !objectp(item = present(arg, me)) )
                return notify_fail("你身上没有这样道具。\n");

        if( !item->is_item_make() ) 
                return notify_fail("你只能锻造自造的防具！\n"); 

        if( !stringp(item->item_owner()) ||
              item->item_owner() != query("id", me) )
                return notify_fail("你只能锻造自己的防具！\n");
        
        if( item->is_weapon() || item->is_unarmed_weapon() )
                return notify_fail("你只能锻造自己的防具！\n");
                
        if( query("equipped", item) )
                return notify_fail("你先解除" + item->name() + "的装备再说！\n"); 

        notify_fail(item->name() + "没有办法被锻造。\n");

        return item->do_forge(me);
}


int help(object me)
{
        write(@HELP
指令格式 : forge <防具>

这个指令可以让你锻造防具，提升防具到准10LV，每次消耗一定的最大内力。

HELP
        );
        return 1;
}

