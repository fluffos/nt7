#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( HIG "蛇胆" NOR , ({"she dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一个浓绿色的蛇胆。\n");
                set("unit", "个");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}