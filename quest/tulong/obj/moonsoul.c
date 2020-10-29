//zhenzhu.c
inherit ITEM;
#include <ansi.h>
void create()
{
        set_name( HIC"月魄"NOR, ({ "moonsoul"}));
        set_weight(300);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long","这是一颗夜明珠，放着幽蓝的柔和的光，它出自月宫，价值连城。\n");
                set("value", 70000);
                set("material", "iron");
              }
}