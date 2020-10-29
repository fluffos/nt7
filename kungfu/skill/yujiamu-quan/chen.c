// fochen.c 佛嗔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "佛嗔"; }

int perform(object me, object target)
{
        int angry;
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「佛嗔」只能对战斗中的对手使用。\n");

        skill = me->query_skill("yujiamu-quan", 1);

        if (skill < 100)
                return notify_fail("你的金刚瑜迦母拳修为不够, 无法使用「佛嗔」！\n");

        if( query("neili", me)<180 )
                return notify_fail("你的真气不够，无法运用「佛嗔」！\n");

        if( objectp(query_temp("weapon", me)) || query_temp("secondary_weapon", me) )
                return notify_fail("「佛嗔」只能空手运用。\n");

        if( angry=query("qi", me)<query("max_qi", me)/2 )
                msg = HIY "$N" HIY "目睚俱裂，一声爆喝，拳头如闪电般击向$n"
                      HIY "的要害！\n" NOR;
        else
                msg = HIY "$N" HIY "大喝一声，拳头如闪电般击向$n"
                      HIY "的要害！\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -150, me);
                me->start_busy(1);
                damage = damage_power(me, "cuff");
                if (angry) damage += random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "结果$p" HIR "无法抵挡$P"
                                           HIR "这雷霆一击，登时被打退数步，摇晃不定。\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "可是$p" CYN "并未被这气势所慑，轻移脚步，躲开了$P"
                       CYN "的攻击。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}