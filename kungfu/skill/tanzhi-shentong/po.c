// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIW "破九域" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage, p;
        string pmsg;
        string msg;
        object weapon, weapon2;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me) )
            || query("skill_type", weapon) != "throwing" )
                return notify_fail("你手中没有拿着暗器，难以施展" + name() + "。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 180)
                return notify_fail("你弹指神通修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("throwing", 1) < 180)
                return notify_fail("你基本暗器修为不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2400 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -300, me);
        weapon->add_amount(-1);

        msg = HIW "陡见$N" HIW "双目精光四射，顿听破空声大作，一" +
              query("base_unit", weapon)+weapon->name()+HIW"由"
              "指尖弹出，疾速射向$n" HIW "。\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("throwing");
        dp = defense_power(target, "dodge") + target->query_skill("parry");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                damage+= query("jiali", me);

                msg+=HIR"只见那"+query("base_unit", weapon)+
                       weapon->name() + HIR "来势迅猛之极，$n" HIR
                       "根本无暇闪避，被这招击个正中！\n" NOR;

                target->receive_wound("qi", damage + fmsk, me); 
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+300);

                if( (weapon2=query_temp("weapon", target) )
                && ap / 3 + random(ap) + fmsk / 2 > dp) 
                {
                        msg += HIW "$n" HIW "手腕一麻，手中" + weapon2->name() +
                               HIW "不由脱手而出！\n" NOR;
                        weapon2->move(environment(me));
                }

                p=query("qi", target)*100/query("max_qi", target);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "早料得$P" CYN "有此一着，急"
                       "忙飞身跃起，躲闪开来。\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}
