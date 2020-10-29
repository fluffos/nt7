// yuce.c

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int skill, i;
        int n, damage;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("御策诀只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("你现在手中并没有拿着暗器，怎么施展御策诀？\n");

        if ((skill = me->query_skill("never-defeated", 1)) < 100)
                return notify_fail("你的不败神功火候不够，不会施展御策诀。\n");

        if( query("neili", me)<150 )
                return notify_fail("你内力不够了。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -120, me);
        weapon->add_amount(-1);

        msg = HIC "$N" HIC "手指一合一弹，只听呼啸破空声起，有若龙吟，一" +
             query("base_unit", weapon)+weapon->name()+HIC"如蛟龙般"+
             "打向$n" HIC "。\n" NOR;

        me->start_busy(1);
        my_exp = attack_power(me, "throwing");
        ob_exp = defense_power(target, "parry");
        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                msg += HIR + "只见那" + weapon->name() + HIR "去势恰如神光闪电！$n"
                       HIR + "不及闪避，被打了个正中，惨叫一"
                       "声，退了几步。\n" NOR;
                       
                damage = damage_power(me, "throwing") * 3 / 2;
                target->receive_wound("qi", damage, me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               query("jiali", me)+150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "急忙一闪，躲过了$P" HIG "发出的" +
                       weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}