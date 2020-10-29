#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "凌空指穴" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("tiangang-zhi") < 100)
                return notify_fail("你的天罡指穴法修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气现在不够，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (me->query_skill_mapped("finger") != "tiangang-zhi")
                return notify_fail("你没有激发天罡指穴法，不能施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "使出天罡指穴法绝技「凌空指穴」，左手"
              "一连七指向着$n" HIC "胸前大穴接连戳出。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");
                ap = ap + ap * me->query_skill("jingxin", 1) / 2000;
                time = 10;
                if ( !userp(target) ) time -= 7;

        if ((ap / 2 + random(ap*3/2) > dp) || !random(time))
        {
                msg += HIR "结果$p" HIR "不及攻敌，拼力躲避$P"
                       HIR "指力顿时动作大乱！\n" NOR;
                time = ap / 250;
                if (time > 180) {
                        time = 180;
                }
                me->start_busy(1);
                        message_combatd(msg, me, target);
                        if (random(10)) target->set_weak(12); 
                target->start_busy(time + 2);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "$p" CYN "情急智生，奋力一跃，退出老远。\n" NOR;
                me->start_busy(3 + random(2));
                        message_combatd(msg, me, target);
                if (random(5)) target->set_weak(6); 
                addn("neili", -50, me);
        }
        return 1;
}


