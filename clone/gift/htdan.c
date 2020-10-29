// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "糊涂丹" NOR, ({ "hutu dan", "dan", "hutu" }) );
        set_weight(200);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗园园很脏的丹药，据说吃了可以降低智力。\n");
                set("value", 10000);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);

        if( query("gift/int/succeed", me)<1 )
        {
                tell_object(me, "不过你觉得好像没什么作用。\n");
        } else
        {
                tell_object(me, HIG "一股火热蓦然从脑中升起，"
                            "你头痛欲裂，恰在此时一股混浊之意"
                            "油然而起，顿感脑子不好使了。\n");
                addn("int", -1, me);
                addn("gift/int/succeed", -1, me);
                if( query("gift/int/all", me)>0 )
                addn("gift/int/all", -1, me);
                addn("gift/xiandan", -1, me);
        }

        destruct(this_object());
        return 1;
}