#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "长明灯" NOR, ({ "changmingdeng for xueyi"}) );
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "\n这是一盏长明灯，为雪忆而明，为雪忆引路，愿其顺利通往天国之路！\n NOR");
                set("value", 1);
                set("unit", "盏"); 
                set("no_get", 1);                
        }
}