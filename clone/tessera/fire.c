// fire.c 炎晶

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED "炎晶" NOR, ({ "yan jing", "fire" }) );
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", RED "这是一块炎晶，地肺熔岩受南明离火所化，色赤红，温度极高。\n" NOR);
                set("value", 2000);
                set("unit", "块");
                set("magic/element", "fire");
        }
        setup();
}