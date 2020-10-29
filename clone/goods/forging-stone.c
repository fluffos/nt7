#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "锻造石" NOR, ({ "forging stone", "forging", "stone" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", YEL "一块拥有神秘魔力的锻造石，和装备一起锻造可升级装备。\n" NOR);
                set("unit", "块");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}
