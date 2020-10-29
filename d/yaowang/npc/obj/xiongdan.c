#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"熊胆"NOR, ({"xiong dan", "xiong"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long", "这是一颗黑熊胆。\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}