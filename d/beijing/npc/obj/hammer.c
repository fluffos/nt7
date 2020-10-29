#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
        set_name( "打铁锤",  ({ "hammer" }));
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "一柄普通的打铁锤。\n");
                set("value", 1000);
                set("material", "gold");
        }
        init_hammer(10);
        setup();
}