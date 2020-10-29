// zhua.c 九阴神抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHUA "「" HIR "九阴神爪" NOR "」"

int perform(object me, object target)
{
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUA "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail(ZHUA "只能空手施展！\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 280)
                return notify_fail("你的九阴神功还不够娴熟，不能使用" ZHUA "。\n");
                                
        if( query("neili", me)<300 )
                return notify_fail("你现在内力太弱，不能使用" ZHUA "。\n");

//        if (me->query_skill_prepared("claw") != "jiuyin-shengong")
        if (me->query_skill_mapped("claw") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" ZHUA "。\n");
       
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "微微一笑，右手成爪，忽的抓向$n"
              HIY "的要穴！\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        me->want_kill(target);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$N" HIR "这一爪来势好快，正抓中$n"
                               HIR "的檀中大穴，$n" HIR
                               "一声惨叫，软绵绵的瘫了下去。\n" NOR;
                        damage = -1;
                } else
                {
                        if (! target->is_busy())
                        target->start_busy(1 + random(3));
        
                        damage = damage_power(me, "claw");
                        
                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n连忙腾挪躲闪，然而“扑哧”一声，$N"
                               HIR "五指正插入$n" HIR "的" + limb + "，$n"
                               HIR "一声惨叫，血溅五步。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的来势，接应得法，避开了这一抓。\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
