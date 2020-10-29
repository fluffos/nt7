#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "凤栖于梧" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int ap,dp,damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("feifeng-bian", 1) < 120)
                return notify_fail("你的飞凤鞭法法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("你现在没有激发飞凤鞭法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "力贯鞭梢，手中" + weapon->name() + HIW "急舞，画"
              "出一个又一个的圈子缠向$n" HIW "！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "只觉得浑身一震，内息有如"
                                           "潮涌，一时不由全身乏力，向后退了一步。\n" NOR);
                msg += HIY "\n$N" HIY "见状，手中" + weapon->name() + HIY +
                       "急挥，一连数招攻向$n" HIY "！\n" NOR;
                message_combatd(msg, me, target);

                for (i = 0; i < 6; i++)
                {
                        if (! me->is_fighting(target))
                                break;
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }

                me->start_busy(1 + random(4));
        } else
        {
                msg += CYN "可是$p" CYN "轻轻架开$P" CYN
                       "这一招，似乎并没有废多少气力。\n" NOR;
                addn("neili", -70, me);
                me->start_busy(3);
                message_combatd(msg, me, target);
        }

        return 1;
}