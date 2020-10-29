#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "海贝壳" NOR, ({ "haibei ke", "haibei", "ke" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIC "一块巨大的海贝壳，似乎可找工匠做成饰品。\n" NOR);
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