#include <ansi.h>
#include <combat.h>

string name() { return HIR "腾诀" NOR; }

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

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("longteng-daofa", 1) < 140)
                return notify_fail("你的龙腾刀法还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "longteng-daofa")
                return notify_fail("你没有激发龙腾刀法，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "嘴角泛起邪意的微笑，猛地加速前冲，左手" + weapon->name() +
              HIR "化作一道白虹，\n顿时一股凌厉无比的无形刀气破空袭向$n" HIR "！\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "只见$n" HIR "一声惨叫，整个人如遭"
                                           "电击，刀气穿心，口中鲜血狂喷而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "默运内力，硬是抵挡了$P"
                       CYN "的这记无形刀气。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
