#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "天然珍珠" NOR, ({ "tianran zhenzhu", "tianran", "zhenzhu" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIC "一颗天然的珍珠，珍贵无比。\n" NOR);
                set("base_unit", "颗");
                set("unit", "颗");
                set("base_value", 200000);
                set("base_weight", 100);
        }
        setup();
}
int query_autoload()
{
        return 1;
}