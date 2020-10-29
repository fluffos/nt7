// jingshi.c 精失诀

#include <ansi.h>

inherit F_SSERVER;

string name() { return "精失诀"; }

int perform(object me)
{
        string msg,str;
        object target;
        int skill, jing_wound, eff_jing_wound, neili_wound;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「精失诀」只能在战斗中使用。\n");

        if( (int)query("neili", me) < 900 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 250 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250)
                return notify_fail("你七伤拳的修为不够，不能够体会精失诀! \n");

        if( (int)me->query_skill("force", 1) < 250)
                return notify_fail(HIM "你的基本内功修为不足，不能随便使用精失诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用精失诀！\n");

        if( me->query_skill_prepared("cuff") != "qishang-quan" )
                return notify_fail("你没有准备使用七伤拳，无法施展「精失诀」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "精失诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
        message_vision(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp || !living(target) )
        {
                addn("neili", -300, me);

                msg = HIG "$N的拳只是轻轻的碰到了$n，但$N的真气趁这一瞬间已流入了$n体内！\n$n只觉得有点疲惫。。。\n"NOR;
                neili_wound = damage_power(me, "cuff");
                neili_wound += query("jiali", me);
                if(neili_wound > query("neili", target))
                        neili_wound = query("neili", target);

                jing_wound = random((int)skill);
                jing_wound += query("jiali", me);
                eff_jing_wound = random((int)skill / 3);
                eff_jing_wound += (int)query("jiali", me)/2;
                target->receive_damage("jing", jing_wound, me);
                target->receive_wound("jing", eff_jing_wound, me);
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1 + random(2));
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;

                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}