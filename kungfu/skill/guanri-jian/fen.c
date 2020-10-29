#include <ansi.h>
#include <combat.h>

string name() { return HIR "焚阳剑" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" +name()+ "。\n");

        if ((int)me->query_skill("guanri-jian", 1) < 150)
                return notify_fail("你观日剑法不够娴熟，难以施展" +name()+ "。\n");

        if (me->query_skill_mapped("sword") != "guanri-jian")
                return notify_fail("你没有激发观日剑法，难以施展" +name()+ "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够，难以施展" +name()+ "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "运转内力，陡然一势「" HIR "焚阳剑" NOR +
              WHT "」划出，手中" + weapon->name() + WHT "携着一股热"
              "流卷向$n" WHT "全身。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           (: final, me, target, damage :));

                me->start_busy(3);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企图，斜跃避开。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("guanri-jian", 1);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "只听$n" HIR "一声惨嚎，几柱鲜血射出，剑伤"
                "处腾起一道烈火，烧得嗤嗤作响。\n" NOR;
}
