// 辟谷符

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "辟谷符" NOR, ({ "bigu fu", "fu" }) );
        set_weight(30);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "携带后进入沙漠地带不会因为无食物饮水而晕倒。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "张");
        }
        set("auto_load", 1);

        setup();
}
