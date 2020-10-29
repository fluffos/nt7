#include <ansi.h> 

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("草莓", ({ "cao mei", "cao", "mei" }));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", RED "这是一颗鲜红硕大的草莓。\n" NOR);
                set("unit", "颗");
                set("value", 10);
                set("food_remaining", 2);
                set("food_supply", 20);
        }
        setup();
}