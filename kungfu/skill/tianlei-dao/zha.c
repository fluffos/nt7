#include <ansi.h>
#include <combat.h>

string name() { return HIY "春雷炸空" NOR; }

inherit F_SSERVER;

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

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("tianlei-dao", 1) < 150)
                return notify_fail("你天雷绝刀不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "tianlei-dao")
                return notify_fail("你没有激发天雷绝刀，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "一声怒喝，内劲瀑涨，施展出绝招「" HIY "春雷炸空" HIW
              "」手中\n" + wn + HIW "出神般的挥舞而出，威力惊人，有如神助一般。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          HIR "$n" HIR "见$N" HIR "来势凶猛，刀"
                                          "光闪烁，惊骇间肩膀已中一刀，一股鲜血"
                                          "喷涌而出。\n" NOR);
                me->start_busy(2 + random(2));
                addn("neili", -240, me);
        } else
        {
                msg = CYN "然而$n" CYN "以快制快，侧身"
                      "一跳，躲过这招。\n" NOR;

                me->start_busy(2);
                addn("neili", -180, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


