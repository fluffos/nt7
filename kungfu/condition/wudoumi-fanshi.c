// wudoumi-fanshi.c
// 五斗米神功反噬

#include <ansi.h>
inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int f, n, lvl;
        f = me->query_skill_mapped("force");
        lvl = me->query_skill("force");

        if (me != ob)
        {
                tell_object(ob, "你发觉" + me->name() + "的内力源源涌进，使丹"
                            "田处燃烧得更为厉害，便如身陷洪炉，眼前登时一黑。\n");
                tell_object(me, "你试图帮助" + ob->name() + "化解异种真气，却"
                            "发现对方真气便似洪炉爆裂，不由大惊，连忙住手。\n");

                if (living(ob))
                        ob->unconcious();

                return -1;
        }

        if (me->query_skill_mapped("force") != "yijin-duangu"
           && me->query_skill_mapped("force") != "jiuyin-shengong"
           && me->query_skill_mapped("force") != "shaolin-jiuyang"
           && me->query_skill_mapped("force") != "wudang-jiuyang"
           && me->query_skill_mapped("force") != "emei-jiuyang"
           && me->query_skill_mapped("force") != "jiuyang-shengong"
           && me->query_skill_mapped("force") != "taiji-shengong"
           && me->query_skill_mapped("force") != "xuanmen-neigong"
           && me->query_skill_mapped("force") != "xiantian-gong")
        {
                tell_object(me, "你觉得全身真气犹如洪炉爆裂，内息"
                                "根本无法凝聚。\n");
                return -1;
        }

        n = me->query_condition("wudoumi-fanshi") - lvl / 15;
        if (n < 1)
                me->clear_condition("wudoumi-fanshi");
        else
                me->apply_condition("wudoumi-fanshi", n);

        tell_object(me, "你默默的运用" + to_chinese(f) + "化解体内"
                        "的异种真气。\n");

        return 1;
}

int update_condition(object me, int duration)
{
	int limit;

	if( !living(me) && (query("eff_qi", me)<20 || query("eff_jing", me)<10) )
        {
                me->set_temp("修习五斗米神功不慎，被内力反噬吐血而亡");
		me->die();
		return 0;
	} else
        {
                me->receive_wound("qi", 200);
                me->receive_wound("jing", 100);

                if( query("max_neili", me) )
                        addn("max_neili", -1, me);

		tell_object(me, HIR "你觉得丹田处如同火烧，全身真气鼓荡"
                                "不止，便似要破体而出一般。\n" NOR);
		message("vision", HIR + me->name() + HIR "脸色赤红，须发"
                                  "焦卷，全身散发着滚滚热气，不住的颤抖。\n",
			          environment(me), me);
	}

        if( query("max_neili", me)<1 )
                set("max_neili", 0, me);

	me->apply_condition("wudoumi-fanshi", duration - 1);

	if (! duration)
                return 0;

	return 1;
}