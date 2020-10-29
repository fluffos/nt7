#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"鹤顶红"NOR, ({"he dinghong"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "滴");
                set("long", "这是一滴鹤顶红，奇毒无比。\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}