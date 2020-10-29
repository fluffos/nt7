// shenliwan.c 神力丸

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "神力丸" NOR, ({ "shenli wan", "wan"}) );
        set_weight(200);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗圆圆的神力丸，据说吃了可以增强臂力。增加先天属性至五点\n");
                set("value", 10000);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);
        if( query("gift/shenliwan", me) >= 5 || 
            query("gift/str/succeed", me) >= 5 )
        {
                message_vision("$N眨眨眼。\n", me);
                tell_object(me, "你觉得这药没啥味道，还不如花生好吃。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/str/fail", 1, me);
                tell_object(me, "不过你觉得好像没什么作用。\n");
        } else
        {
                tell_object(me, HIR "你觉得双臂几乎爆裂，充满了力量。\n" NOR);
                addn("str", 1, me);
                addn("gift/str/succeed", 1, me);
        }

        if( query("gift/shenliwan", me)<5 )
                addn("gift/shenliwan", 1, me);
        destruct(this_object());
        return 1;
}