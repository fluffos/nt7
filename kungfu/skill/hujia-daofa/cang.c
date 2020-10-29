#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "八方藏刀势" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 180)
                return notify_fail("你的胡家刀法还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你没有激发胡家刀法，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "轻舒猿臂，施出「战八方藏刀式」，手中的" + weapon->name() +
              HIW "吞吞吐吐，变化莫测，笼罩了$n" HIW "周身要害！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "见来招实在是变幻莫测，不由得心"
                       "生惧意，招式登时出了破绽！\n" NOR;
                count = me->query_skill("hujia-daofa", 1)/2;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，打起精神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -220, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}
