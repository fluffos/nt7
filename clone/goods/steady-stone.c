#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "强化石" NOR, ({ "steady stone", "steady", "stone" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", YEL "一块拥有神秘魔力的强化石，和装备一起冶炼可强化装备基本属性。\n" NOR);
                set("unit", "块");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}
