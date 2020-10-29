#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( WHT "蛇毒" NOR , ({"she du"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一滴浊白色的蛇毒。\n");
                set("unit", "滴");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}