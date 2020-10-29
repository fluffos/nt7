// This program is a part of NITAN MudLIB
// jiutian.c 九天式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九天式"; }

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
                return notify_fail("「九天式」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 120)
                return notify_fail("你的六阳掌法不够娴熟，不会使用「九天式」。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高，难以运用「九天式」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，不能使用「九天式」。\n");

        msg = HIC "$N" HIC "双掌一振，化出满天掌影，团团笼罩住$n" HIC "！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$p" HIR "无奈，只能硬挡一招，结果被$P"
                                           HIR "震得连退数步，吐血不止！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "强运内力，硬生生的挡住$P"
                       HIC "这一掌，没有受到任何伤害！\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}