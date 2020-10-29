#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "闪刀诀" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，难以施展"+name()+"。\n");

        if ((int)me->query_skill("liuhe-dao", 1) < 80)
                return notify_fail("你的六合刀法还不到家，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("blade") != "liuhe-dao")
                return notify_fail("你没有激发六合刀法，难以施展"+name()+"。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真气不够，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手中的" + weapon->name() +  HIW "吞吐不定，接连"
              "变换了数种方位，最后呼的一声朝$n" HIW "砍落！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只见$n" HIR "招架不及，顿时被$N"
                                           HIR "这一刀砍中要害，伤口见骨，鲜血狂溅！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "凝神聚气，护住门户，无论$P"
                       CYN "怎样变招，始终奈何不得。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}