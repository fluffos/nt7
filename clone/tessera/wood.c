// wood.c 木灵

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "木灵" NOR, ({ "mu ling", "wood" }) );
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIG "这是一片木灵，来自东海扶桑之树，上古神人所栖，每千年而有木灵生，色青，触之若无物。\n" NOR);
                set("value", 2000);
                set("unit", "片");
                set("magic/element", "wood");
        }
        setup();
}