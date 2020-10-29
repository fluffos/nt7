// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "寰阳式" NOR; }

inherit F_SSERVER;

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
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 130)
                return notify_fail("你的天山六阳掌不够娴熟，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "双掌一振，施出天山六阳掌「寰阳式」，幻出"
              "满天掌影，团团罩住$n" HIR "。\n" NOR;

        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$n" HIR "见躲闪不得，只能硬挡下一"
                                           "招，顿时被$P" HIR "震得连退数步，吐血"
                                           "不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "可是$p" HIC "强运内力，硬生生的挡住$P"
                       HIC "这一掌，没有受到任何伤害。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
