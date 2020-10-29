#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( HIR "鹿血" NOR , ({"lu xue", "xue"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一滴梅花鹿血。\n");
                set("unit", "滴");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}