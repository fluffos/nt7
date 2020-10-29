#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "雄霸群山" NOR; }

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

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("chuangwang-dao", 1) < 40)
                return notify_fail("你的闯王刀法还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "chuangwang-dao")
                return notify_fail("你没有激发闯王刀法，难以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "一声怒喝，手中" + weapon->name() +  HIY "凌空劈斩"
              "而出，刀锋顿时如闪电般贯向$n" HIY "！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "稍作迟疑，不想被$N" HIR
                                           "一刀劈中，顿时一声惨呼，血溅五步！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "微微一笑，身子朝一旁偏过尺许，躲开$P"
                       CYN "这一刀。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}