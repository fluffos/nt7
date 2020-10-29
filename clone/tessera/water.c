// water.c 玄冰

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "玄冰" NOR, ({ "xuan bing", "water" }) );
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIC "这是一块玄冰，极北万年冰山所孕，色玄黑，寒气逼人。\n" NOR);
                set("value", 2000);
                set("unit", "块");
                set("magic/element", "water");
        }
        setup();
}