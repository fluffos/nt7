// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "伏魔剑诀" NOR; }

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

        if ((int)me->query_skill("yitian-jian", 1) < 120)
                return notify_fail("你的倚天剑法不够娴熟，无法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你没有激发倚天剑法，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声冷哼，手中" + weapon->name() +
              HIW "一振，剑身微颤，声若龙吟，剑光携着数个剑花"
              "同时洒向$n" HIW "。\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "sword");
        ap += me->query_skill("mahayana");
        ap += me->query_skill("jingxin", 1) * 10;
        dp = defense_power(target, "parry");
          if (target->is_bad()) ap += ap / 3;


        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                  damage += query("jiali", me) / 2;
                       damage += damage * me->query_skill("jingxin", 1) / 2000; 
                       damage += damage * me->query_skill("mahayana", 1) / 5000; 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           (: final, me, target, damage :));
                me->start_busy(1 + (random(5) ? 0 : 1));
        } else
        {
                msg += HIC "可$n" HIC "却是镇定逾恒，一丝不乱，"
                       "全神将此招化解开来。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "只听$n" HIR "一声惨叫，被这一剑穿胸而入，顿"
                "时鲜血四处飞溅。\n" NOR;
}
