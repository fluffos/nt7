#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "无孔不入" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你所使用的武器不对，难以施展" +name()+ "。\n");

        if ((int)me->query_skill("sanwu-shou", 1) < 140)
                return notify_fail("你三无三不手够娴熟，难以施展" +name()+ "。\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你没有激发三无三不手，难以施展" +name()+ "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的内功修为不够，难以施展" +name()+ "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = HIY "\n$N" HIY "一声长啸，内劲暴涨，施出绝招「" HIW "无孔"
              "不入" HIY "」手中" + weapon->name() + HIY "哧哧作响，龙"
              "吟不定，\n$N" HIY "猛然腾空而起，挥舞着手中的" + weapon->name() +
              HIY "，凌空直下，涌向$n" HIY "。\n" NOR;
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "但见$N" HIR "攻势如洪，气势磅礴，"
                                           "$n" HIR "心中略微一惊，惨叫一声，顿"
                                           "时鲜血淋淋。\n" NOR);

                me->start_busy(2);
                addn("neili", -220, me);
        } else
        {
                msg = CYN "$n" CYN "见$N" CYN "这招袭来，内力"
                      "充盈，只得向后一纵，才躲过这一鞭。\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
