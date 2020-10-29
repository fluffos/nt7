#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "佛" HIM "光" HIC "宝珠" NOR, ({ "foguang baozhu", "foguang", "baozhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "这是一粒闪耀着佛光的宝珠，光芒四射，人间罕有。\n" NOR);
                set("base_unit", "粒");
                set("unit", "粒");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}