#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "奇剑诀" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "sword")
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 160)
                return notify_fail("你逍遥剑法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你没有激发逍遥剑法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("你内力修为不足，难以施展" + name() + "。\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "将" + wn + HIW "斜指长空，猛地飞身跃起，"
              + wn + HIW "忽左忽右，飘忽不定，猛然间破空长响，" + wn + HIW
              "直指向$n" HIW "咽喉。\n这正是逍遥剑法之「" HIG "奇剑诀" HIW "」，"
              "当真是招招精奇，神妙无比。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                          HIR "$n" HIR "只见一道电光从半空袭来，"
                                          "心中惊骇不已，但鲜血已从$n胸口喷出。\n"
                                          NOR);
                me->start_busy(2 + random(4));
                addn("neili", -300, me);
        } else
        {
                msg = CYN "然而$n" CYN "眼明手快，侧身一跳"
                      "躲过$N" CYN "这一剑。\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
