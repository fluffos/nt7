// jin.c 神魔金身
// Created by rcwiz for yhonline

#include <ansi.h>

int is_scborn() { return 1; }

string name() { return HIC "神魔金身" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int i;

        if ((int)me->query_temp("special2/jin"))
                return notify_fail("你神魔金身之术已在施展中了。\n");

        message_vision(HIY "$N" HIY "施展出神魔金身之术，刹那间全身真气迸发，犹如蚩尤再现，威猛无比！\n" NOR, me);

        i = me->query_skill("force");

        if (i < 100)i = 100;

        me->add_temp("apply/armor", i * 3);
        me->set_temp("special2/jin", 1);
        me->add_temp("apply/parry", 200);      
 
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, i * 3 :), i);

        return 1;
}

void remove_effect(object me, int amount)
{
	if (! objectp(me))return;
	
        if (me->query_temp("special2/jin"))
        {
                me->add_temp("apply/armor", -amount);
                me->delete_temp("special2/jin");
                me->add_temp("apply/parry", -200);
                tell_object(me, "你神魔金身之术已施展完毕。\n");
        }
        
}
