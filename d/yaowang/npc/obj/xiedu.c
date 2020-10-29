#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( BLU "蝎毒" NOR , ({"xie du"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一滴无色透明的蝎毒。\n");
                set("unit", "滴");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}