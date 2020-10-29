#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"断肠草"NOR, ({"duanchang cao", "duanchang"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "株");
                set("long", "这是一株断肠草，奇毒无比。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}