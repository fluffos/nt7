#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "风神诀" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon, weapon2;
        string w1, w2;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你的武器不对，无法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("你没有激发回银索金铃，不能使用" + name() + "。\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 140)
                return notify_fail("你的银索金铃不够娴熟，还使不出" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("neili", me)<400 )
               return notify_fail("你现在真气不够，难以施展" + name() + "。\n"NOR);

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        w1 = weapon->name();
        damage = damage_power(me, "whip");
        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = "\n" HIW "只见$N" HIW "手中" + w1
              + HIW "暮地一抖，幻出无数鞭影，霎"
              "时破风声骤起，" + w1 + HIW "携着"
              "风雷之势扫向$n" HIW "！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "只觉鞭影重重，眼花缭乱"
                                           "，根本无法作出抵挡，一声惨嚎，鲜血飞"
                                           "溅而出！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "镇定自如，"
                       "丝毫不为这变幻莫测的招式所动"
                       "，凝神抵挡，化解开来！\n" NOR;
        }

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        msg += "\n" HIW "紧接着$N" HIW "一声"
               "娇喝，" + w1 + HIW "猛地向后"
               "一撤，" + w1 + HIW "顿时化作"
               "一道长虹，已从$n" HIW "背后"
               "袭出！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "稍一迟疑，突然感到后背"
                                           "一阵" HIR "刮骨之痛，已被这招打得血"
                                           "肉模糊！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "一声冷哼，早预料$N"
                       CYN "有此一着，凝神聚气，将这招轻"
                       "轻格开！\n" NOR;
        }

        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg += "\n" HIW "$N" HIW "眉头微皱，手"
                       "腕轻轻一振，只听“飕”的一声，"
                       "又攻出一招，" + w1 + HIW "如流"
                       "星般弹向$n" HIW "腕部！\n" NOR;

                ap = attack_power(me, "whip");
                dp = defense_power(target, "force");

                if (ap / 2 + random(ap) > dp)
                {
                        w2 = weapon2->name();
                        msg += HIR "只听“当”的一声，" + w1 +
                               HIR "正打在$p" + w2 + HIR "上，"
                               "$p" HIR "手腕一麻，" + w2 + HIR
                               "再也拿持不住，脱手掉在地上。\n"
                               NOR;
                        addn("neili", -50, me);
                        weapon2->unequip();
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "可是$p" CYN "看破了$P" CYN
                               "的企图，急忙斜跳躲开！\n" NOR;
                        addn("neili", -30, me);
                }
        }
        me->start_busy(2 + random(4));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}