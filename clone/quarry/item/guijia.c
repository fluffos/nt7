#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "龟甲" NOR, ({ "gui jia", "gui", "jia" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "乌龟的甲壳，不错的铸造材料。\n" NOR);
                set("base_unit", "块");
                set("unit", "块");
                set("base_value", 10000);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}