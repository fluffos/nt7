
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "鬼影流星" NOR; }

int perform(object me, string skill, string arg)
{
	int add_dam;

        if (me->query_temp("special/guiying"))
                return notify_fail("鬼影流星技能已经在施展中了。\n");

        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        message_vision(HIY "$N" HIY "凝神闭气，将数股真气同时催动，沿各处经脉运转一个周天，刹时身法变得飘逸无比 ……\n" NOR, me);
 
        me->start_busy(1);

	add_dam = 1 + me->query_skill("dodge") * 2 / 25;
	
        me->set_temp("special/guiying", 1);
	me->add_temp("apply/dodge", add_dam);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, add_dam :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/guiying"))
        {
		me->add_temp("apply/dodge", -1 * add_dam);
	        me->delete_temp("special/guiying");
	        tell_object(me, "你鬼影流星技施展完毕。\n");
        }
}

