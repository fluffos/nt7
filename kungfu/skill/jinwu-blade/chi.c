#include <ansi.h>
#include <combat.h>

string name() { return HIY "赤焰暴长" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon, weapon2;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，无法施展" + name() + "。\n");

        if ((int)me->query_skill("jinwu-blade", 1) < 120)
                return notify_fail("你的金乌刀法不够娴熟，无法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "jinwu-blade")
                return notify_fail("你没有激发金乌刀法，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "凝神聚气，将全身之力注入" + weapon->name() +
              HIY "刀身顺势劈下，顿时一股凌厉的刀芒直贯$n" HIY "而去。\n"
              NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if( objectp(weapon2=query_temp("weapon", target) )
            && query("skill_type", weapon2) == "sword"
           && target->query_skill_mapped("sword") == "xueshan-jian")
        {
                msg += HIY "$n" HIY "慌忙中忙以雪山剑法作出抵挡，哪知$N"
                       HIY "刀法竟似雪山剑法克星般，" + weapon->name() +
                       HIY "焰芒霎时\n又暴涨数倍，完全封锁$n" HIY "的所"
                       "有剑招！\n" NOR;
                ap += ap / 2;
        }

        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
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
        return  HIR "只听$n" HIR "一声惨叫，被这一刀劈个正中，伤口"
                "深可见骨，鲜血四处飞溅。\n" NOR;
}
