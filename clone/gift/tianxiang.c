// tianxiang.c 天香玉露

#include <ansi.h>

#include "gift.h"

void create()
{
        set_name(HIG "天香玉露" NOR, ({"magic water", "yvlu", "lu"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "些");
                set("base_unit", "滴");
                set("long", HIG "这是附着在灵芝上的一滴晶莹剔透的玉露，传说采自\n"
                                "灵山，千年来以灵芝为母，不断的吸取着日精月华，\n"
                                "具有着无比神奇的功效。\n");
                set("base_value", 100000); 
                set("base_weight", 200);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string force;
        int neili_limit;

        neili_limit = me->query_current_neili_limit();
        message_vision(HIG "$N" HIG "小心翼翼的将玉露含在嘴中，登时觉得"
                       "灵台一阵空明，浑身上\n下飘飘欲仙，一时间竟有不在"
                       "尘世的感觉。\n" NOR,
                       me);

        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 120+random(150), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

        }

        if( query("gift/tianxiang", me) <= 200 )
        {
        force = me->query_skill_mapped("force");
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 40000);
        if (stringp(force) && me->can_improve_skill(force))
                me->improve_skill(force, 40000);
        }

        addn("gift/tianxiang", 1, me);
        // me->start_busy(random(5) + 5);
        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
        
        return 1;
}