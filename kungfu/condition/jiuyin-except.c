// qiankun-except.c

#include <ansi.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	int limit;

	if (! living(me) && (query("eff_qi", me) < 100 || query("eff_jing", me) < 50))
        {
                set_temp("die_reason", "因为强自修炼逆九阴心法，走火入魔而死", me);
		me->die();
		return 0;
	} else
        {
                me->receive_wound("qi", 100);
                me->receive_wound("jing", 50);
		tell_object(me, HIR "你觉得丹田阵阵寒冷，可是脸上却"
                            "好像发烧一样火热之极。\n" NOR);
		message("vision", me->name() + "脸色忽青忽红，强忍着运功抗争。\n",
			environment(me), me);
	}

	return 1;
}