// card.c
#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIC "三万两建房卡" NOR, ({"fee free card"}));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long",HIC "这是一张价值三万两黄金的建房卡，把他交给鲁班可以建相应价值的房屋。\n" NOR);
                set("value", 1);
                                set("fee free", 30000);
                set_weight(100);
        }
        setup();
}

int query_autoload()
{
        return 1;
}