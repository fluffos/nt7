// hun.c 飞龙升天

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;
        string *limbs,limb;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("feilong-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("飞龙升天只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "feilong-cuff") 
                return notify_fail("你没有用飞龙神拳，无法使用「飞龙升天」绝招！\n");

        if (me->query_skill_prepared("cuff") != "feilong-cuff")
                return notify_fail("你没有准备使用飞龙神拳，无法施展「飞龙升天」绝招。\n");

        if (skill < 100)
                return notify_fail("你的飞龙神拳等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用拳法绝招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIW "\n$N" HIW "默运运起飞龙神拳的" HIC "飞龙升天" HIW "，忽的长啸一声，双拳电闪击出。\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIR "\n$N" HIR "双拳宛若布下天罗地网式，招招击向$n" HIR "的关节要害！\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                limbs=query("limbs", target);
                limb = limbs[random(sizeof(limbs))];
                msg += HIB "$n" HIB "大惊失色，连连中招，竟被$N" HIB "击中" + limb + "！\n"NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIY "$n" HIY "不退反进，长袖一圈一带，$N" HIY "竟递不进招去。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

