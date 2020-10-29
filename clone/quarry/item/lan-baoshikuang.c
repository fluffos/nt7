#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "蓝宝石矿" NOR, ({ "lan baoshikuang", "lan" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "块");
                set("unit", "块");
                set("base_value", 10000);
                set("base_weight", 600);
        }
        setup();
}
int query_autoload()
{
        return 1;
}