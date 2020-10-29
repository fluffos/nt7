// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "毁容丸" NOR, ({ "huirong wan", "wan", "huirong" }) );
        set_weight(200);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗园园的丹丸，据说吃了可以变的越来越丑，真不知道谁还要这个东西耶。\n");
                set("value", 10000);
                set("unit", "粒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一粒" + this_object()->name() +
                       "。\n", me);
        if( query("per", me) <= 13 )
        {
                message_vision("$N忽然“哇哇”，吐了一地。\n", me);
                tell_object(me, "你觉得嘴里非常的苦。\n");
        } else
        {
                tell_object(me, HIG "你开始发觉你的容貌开始改变，变的难看多了。\n" NOR);
                addn("per", -1, me);
        }

        destruct(this_object());
        return 1;
}