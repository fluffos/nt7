#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "千姿百媚" NOR; }

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("yunv-jian", 1) < 40)
                return notify_fail("你玉女剑法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你没有激发玉女剑法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的轻功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "陡然间姿态万千，身法飘逸，犹如一个婀娜"
              "多姿的女子在随歌漫舞一样。\n但是$N手中" + wn + HIC "却"
              "跟随着身体轻盈地晃动，看似毫无章法，却又像是隐藏着厉"
              "害的招式。" NOR;

        message_combatd(msg, me, target);

        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "看不出$n" HIY "招式中的虚实，连忙"
                      "护住自己全身，一时竟无以应对！\n" NOR;
                target->start_busy(2 + random(ap / 90));
        } else
        {
                msg = CYN "可是$N" CYN "看出了$n" CYN "这招乃虚招，顿"
                      "时一丝不乱，镇定自若。\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}