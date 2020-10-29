#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "佛光初现" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，无法施展" + name() + "。\n");

        if ((int)me->query_skill("emei-jian", 1) < 60)
                return notify_fail("你的峨嵋剑法不够娴熟，无法施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "emei-jian")
                return notify_fail("你没有激发峨嵋剑法，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "跨步上前，手中" + weapon->name() +
              HIY "将峨眉剑法运转如飞，剑光霍霍径直逼向$n"
              HIY "。\n" NOR;

        addn("neili", -75, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可$n" HIC "却是镇定逾恒，一丝不乱，"
                       "全神将此招化解开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "顿时只听“嗤”的一声，$n" HIR "稍个不慎，"
                "被这一剑划得鲜血淋漓。\n" NOR;
}
