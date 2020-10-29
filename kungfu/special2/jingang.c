
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "金刚护体" NOR; }

int perform(object me, string skill, string arg)
{
        int add_dam;      	

        if (me->query_temp("special/jingang"))
                return notify_fail("金刚护体技能已经在施展中了。\n");

        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        message_vision(HIY "$N" HIY "双拳挥出，大喝一声，猛然间全身金光笼罩，皮肤犹如渡上一层金子一般 ……\n" NOR, me);
 
        me->start_busy(1);

        me->set_temp("special/jingang", 1);
	me->add_temp("apply/armor", 500);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, 500 :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/jingang"))
        {
		me->add_temp("apply/armor", -500);
	        me->delete_temp("special/jingang");
	        tell_object(me, "你金刚护体特技施展完毕。\n");
        }
}

