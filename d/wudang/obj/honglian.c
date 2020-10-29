//honglian.c 小红莲

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIR"小红莲"NOR, ({"hong lian", "honglian"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                set("long", "这是一朵红色小花，象极了一个小莲座。\n");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N把" + name() + "扔进嘴里，几下就吞了下去。\n", me);
        addn("neili", 100, me);
        if( query("neili", me)>query("max_neili", me) )
                set("neili",query("max_neili",  me), me);
        destruct(this_object());
        return 1;
}
