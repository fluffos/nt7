// unknow.c 未名仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "火红仙丹" NOR, ({ "huohong xiandan", "dan", "xiandan" }));
        set_weight(200);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗园园的火红仙丹，据说吃了可以增强身法。增加先天属性至五点\n");
                set("value", 10000);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);
        if( query("gift/unknowdan", me) >= 5 || 
            query("gift/dex/succeed", me) >= 5 )
        {
                message_vision("$N摇摇晃晃的，突然“啪嗒”一下子摔了个跟头。\n", me);
                tell_object(me, "你觉得吃完以后头重脚轻的。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/dex/fail", 1, me);
                tell_object(me, "不过你觉得好像没什么作用。\n");
        } else
        {
                tell_object(me, HIM "霎时间你觉得腿骨欲裂，一时疼痛难"
                            "忍，几乎晕了过去。\n" NOR);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/unknowdan", me)<5 )
                addn("gift/unknowdan", 1, me);
        destruct(this_object());
        return 1;
}