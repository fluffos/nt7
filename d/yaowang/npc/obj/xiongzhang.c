#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"熊掌"NOR, ({"xiong zhang"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "只");
                set("long", "这是一只黑熊掌。\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}