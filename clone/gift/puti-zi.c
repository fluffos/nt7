// puti-zi.c 菩提子

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIG "菩提子" NOR, ({"puti zi", "zi"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "这是一颗晶莹如玉的菩提子，采自灵山佛祖座"
                            "前，珍稀无比，\n乃万年菩提树之实，功能化百劫"
                            "，渡千灾，与天地同寿。\n");
                set("base_value", 50000);
                set("base_weight", 100);
                set("base_unit", "颗");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int neili_limit;

        neili_limit = me->query_current_neili_limit();
        if ((int)me->query_condition("putizi_drug") > 0)
        {
                write("你觉得现在内息未定，经脉隐隐还能感到真气冲荡，不"
                      "敢贸然服食。\n");
                return 1;
        } else
        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 100+random(30), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

                message_vision(HIY "$N" HIY "吃下一颗菩提子，顿然间只觉一股浩"
                               "荡无比的真气直冲顶门，连忙运功吸纳。\n" NOR,
                               me);
                // me->apply_condition("putizi_drug", 50);
        } else
        {
                message_vision(HIY "$N" HIY "一仰脖，吞下了一颗菩提子。\n" NOR,
                               me);
                tell_object(me, "你觉得没啥感觉，不如花生好吃。\n");
        }

        // me->start_busy(random(5) + 5);
        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
                
        return 1;
}