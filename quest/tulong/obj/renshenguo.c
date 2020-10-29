// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR"人参果"NOR, ({"guo", "renshen guo"}));
        set("unit", "朵");
        set("long", "这是一只人参果, 已经成型, 真的象极了三周不满的小孩。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("你要吃什么？\n");
        if(arg=="guo")
        {
                addn("max_neili", 10, me);
                set("neili",query("max_neili",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                message_vision("$N吃下一枚人参果，只觉得精神健旺，气血充盈，体内真力源源滋生，甚至不再感到饥饿干渴!\n",me);

                destruct(this_object());
        }
        return 1;
}