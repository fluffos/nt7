// xiongdan.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        remove_call_out("destdan");
        call_out("destdan", 10);
}

void destdan()
{
        object ob;
        message_vision("$N慢慢被风吹着，一会就不再新鲜了。\n",this_object());
        ob = new("/d/guanwai/npc/xiongdan1");
        ob->move(environment(this_object()));
        destruct(this_object());
}

void create()
{
        set_name(HIG"新鲜熊胆"NOR, ({"dan", "xiong dan"}));
        set("unit", "副");
        set("long", "这是一副新鲜熊胆，热气腾腾的，十分诱人。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("你要吃什么？\n");
        if (me->is_fighting()) return notify_fail("战斗中不能吃东西！\n");
        if (me->is_busy()) return notify_fail("你正忙着呢！\n");
        if(arg=="dan")
        {
                addn("max_neili", 2, me);
                set("neili",query("max_neili",  me), me);
                set("qi",query("eff_qi",  me), me);
                message_vision("$N吃下一副新鲜熊胆，只觉得精神健旺，体内真力源源滋生，气血充盈。\n",me);

                destruct(this_object());
        }
        return 1;
}
