// wanli.c 晴空万里

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object  weapon;
        int     damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("晴空万里只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("never-defeated", 1) < 120)
                return notify_fail("你的不败神功还不够娴熟，不能使用晴空万里。\n");
                                
        if( query("neili", me)<200 )
                return notify_fail("你现在内力太弱，不能使用晴空万里。\n");
                        
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须手持兵刃才能施展晴空万里！\n");
                
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("你现在没有激发不败神功为剑法，难以施展晴空万里。\n"); 
                
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "怀抱" + weapon->name() + HIC "，一"
              "圈圈的划向$n" HIC "，将$p" HIC "卷在当中！\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);

                damage = damage_power(me, "sword");

                if( arrayp(limbs=query("limbs", target)) )
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "要害";
                pmsg = HIR "$n连忙腾挪躲闪，然而“扑哧”一声，" + weapon->name() +
                       HIR "正好击中$p" HIR "的" + limb + "，$p"
                       HIR "一声惨叫，连退数步。\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
        } else 
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的变化，见招拆招，没有受到任何伤害。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
