#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT"何首乌"NOR, ({"heshou wu", "heshou", "wu"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "棵");
                set("long", "这是一棵初具人形的何首乌。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}