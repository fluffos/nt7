// wlywine.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
        string *order = ({HIW "五粮液" NOR,HIM "剑南春" NOR, HIY "全兴大曲" NOR, HIR "文君" NOR, HIG "古井贡酒" NOR});
        set_name( (order[random(5)]), ({ "wine" }) );
        set_weight(10);
        /*if( clonep() )
             set_default_object(__FILE__);
        else*/ {
        set("long", "一瓶名酒。\n");
                set("unit", "瓶");
                set("value", 0);
                set("max_liquid", 20);
        }
        // The liquid contained in the container is independent, we set a copy
        // in each cloned copy.
        set("liquid", ([
                "type": "alcohol",
                "name": "酒",
                "remaining": 20,
                "drunk_apply": 5,
        ]) );
}