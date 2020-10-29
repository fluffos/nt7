// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "一气化三清" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;
        int is_yunv = 0;
        int fmsk = me->query_skill("huajia-su", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("你全真剑法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("你的先天功不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你没有激发全真剑法，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声长吟，将内力全然运到剑上，" + weapon->name() +
              HIW "剑脊顿时" HIM "紫芒" HIW "闪耀，化作数道剑气劲逼$n"
              HIW "。\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (stringp(target->query_skill_mapped("sword")) &&
            target->query_skill_mapped("sword") == "yunv-jian" &&
            query_temp("weapon", target) &&
            query("skill_type", query_temp("weapon", target)) == "sword")
        {
                dp += target->query_skill("yunv-jian", 1);
                is_yunv = 1;
        }

        me->start_busy(3);
        addn("neili", -200, me);

        if (ap / 2 + random(ap) > dp)
        {	
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100+fmsk/100,
                                           HIR "顿时只听$n" HIR "一声惨叫，剑气及"
                                           "身，身上接连射出数道血柱。\n" NOR);
                message_combatd(msg, me, target);

                if (ap / 2 + random(ap) > dp)
                {
                        count = me->query_skill("xiantian-gong", 1) / 2;
                        addn_temp("apply/attack", count, me);
                        message_combatd(HIY "$N" HIY "见$n" HIY "在这一击之下破"
                                        "绽迭出，顿时身形前跃，唰唰唰又是三剑。"
                                        "\n" NOR, me, target);

                        for (i = 0; i < 3; i++)
                        {
                                if (! me->is_fighting(target))
                                        break;
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }
                        addn_temp("apply/attack", -count, me);
                }
        } else
        {
                if (is_yunv)
                        msg += CYN "却见$n" CYN "微微一笑，反手一招“玉女剑法”，轻松地档住了$N的剑招。\n" NOR;
                else
                        msg += CYN "可是$n" CYN "看破了$N" CYN "的企图，斜跃避开。\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}
