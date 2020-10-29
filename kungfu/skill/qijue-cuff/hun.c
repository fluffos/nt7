// hun.c 混天七绝

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("qijue-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("混天七绝只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "qijue-cuff") 
                return notify_fail("你没有用七绝拳，无法使用「混天七绝」绝招！\n");

        if (me->query_skill_prepared("cuff") != "qijue-cuff")
                return notify_fail("你没有准备使用七绝拳，无法施展「混天七绝」绝招。\n");

        if (skill < 100)
                return notify_fail("你的七绝拳等级不够，练好了再来！\n");

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

        msg = HIY "\n$N" HIY "满场游走，突然大喝一声，$n" HIY "一惊之际，$N" HIY "双拳挥动，\n"
              HIY "已向$n" HIY "全身上下连续击出数拳！拳头雨点般闪向$n。\n" NOR;
        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "一阵拳雨过去，$n" HIW "正待缓过气来，不料$N" HIW "布满内家真力的双拳又迎面击来！\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIY "只听得“咔嚓”一声，$n" HIY "一阵剧痛，哇地一声吐出一口" HIR "鲜血" HIY "，结结实实地被命中一拳。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "急运内功，全身布满真气，迎着$N" HIW "的拳路，“砰砰”几响，与$N" HIW "斗了一个旗鼓相当！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

