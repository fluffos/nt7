#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "鸿蒙灵气" NOR, ({ "hongmeng lingqi", "hongmen lingqi", "lingqi" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIR "混沌初开产生的鸿蒙灵气，据说拥有着奇幻的力量，是用来提升套装等级的必备材料。\n" NOR); 
                set("unit", "块");
                set("value", 500000);
                set("no_sell", 1);
                set("auto_load", 1);
        }
        setup();
}
