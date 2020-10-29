
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "舍我其谁" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
		object *t;
		object tob;
		int qi, jing;

		joblv = me->query_joblv();

		t = me->query_team(); // 必须要组队才能施展

        if (time() - me->query_temp("special2/shewo/lasttime") < 60)
                return notify_fail("该技能在一分钟内只能施展一次。\n");

		if (me->query("yhjob/job") != "侠客")
				return notify_fail("你的职业错误，无法施展。\n");
		
		if (me->query("neili") < 1000)
				return notify_fail("你的内力不足，无法施展。\n");

		if (joblv < 30)
				return notify_fail("你的职业等级不足，无法施展。\n");		

		if (! arrayp(t))
				return notify_fail("该技能只能在组队的时候施展。\n");

	    t -= ({ 0 });
		if (sizeof(t) <= 1)
				return notify_fail("该技能只能在多人组队的时候施展。\n");
			
        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        message_vision(HIC "$N" HIC "双目微闭，顿时全身上下被一道金光笼罩，慢慢地，金光扩散开来 …………\n" NOR, me);

		foreach (tob in t)
		{
			if (! objectp(tob))continue;

			if (1)
			{			
				tell_object(tob, HIW + me->name() + "施展出绝招「舍我其谁」，恢复所有队友的精力及气血。\n" NOR);
				qi = 500 + me->query_joblv() * 50 + me->query("lhpoint/special/shewo")* 400;
				jing = 200 + me->query_joblv() * 30 + me->query("lhpoint/special/shewo") * 300;

				// 恢复受伤状态
				if (tob->query("eff_qi") + qi / 2 > tob->query("max_qi"))
						tob->set("eff_qi",tob->query("max_qi"));
				else
						tob->add("eff_qi", qi / 2);

				// 恢复气血
				if (tob->query("qi") + qi > tob->query("eff_qi"))
						tob->set("eff_qi", tob->query("eff_qi"));
				else
						tob->add("qi", qi);
				
				// 恢复精力/精气受伤状态
				if (tob->query("eff_jing") + jing / 2 > tob->query("max_jing"))
						tob->set("eff_jing", tob->query("max_jing"));
				else
						tob->add("eff_jing", jing / 2);

				if (tob->query("eff_jingli") + jing / 4 > tob->query("max_jingli"))
						tob->set("eff_jingli", tob->query("max_jingli"));
				else
						tob->add("eff_jingli", jing / 4);

				if (tob->query("jing") + jing / 2 > tob->query("eff_jing"))
						tob->set("jing", tob->query("eff_jing"));
				else
						tob->add("jing", jing / 2);

				if (tob->query("jingli") + jing / 2 > tob->query("eff_jingli"))
						tob->set("jingli", tob->query("eff_jingli"));
				else
						tob->add("jingli", jing / 2);
			}
		}
 
		me->set_temp("special2/shewo/lasttime", time());
        me->add("neili", -1000);
        me->start_busy(1);

        return 1;
}
