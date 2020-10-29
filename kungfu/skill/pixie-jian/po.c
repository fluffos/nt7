#include <ansi.h>
#include <combat.h>

string name() { return HIW "破元剑闪" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

string *finger_name = ({ "左手中指", "左手无名指", "左手食指",
                         "右手中指", "右手无名指", "右手食指", });

int perform(object me, object target)
{
        int damage;
        string msg, name;
        object weapon;
        int lvl, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        weapon=query_temp("weapon", me);

        if (! objectp(weapon))
                return notify_fail("你没有使用兵器，无法施展" + name() + "。\n");

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("pixie-jian", 1) < 180)
                return notify_fail("你的辟邪剑法不够娴熟，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2600 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你没有准备使用辟邪剑法，难以施展" + name() + "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("你没有准备使用辟邪剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        /*
        if( query_temp("no_perform", target) )
                return notify_fail("对方现在已经无法控制真气，放胆攻击吧。\n");
        */

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIW "$N" HIW "一声冷哼，双眸间透出一丝寒气，" + name +
              HIW "化作千百根相似，幻出死亡的色彩！\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap*2) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, random(15) + 100,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "大惊之下全然无法招架，急忙"
                       "抽身急退数尺，躲开了这一招。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_conditon("no_perform")) return "";
        target->apply_condition("no_perform", 30);
        remove_call_out("poyuan_end");
        call_out("poyuan_end", 10 + random(ap / 30), me, target);
        return HIR "$n" HIR "只觉眼前寒芒一闪而过，随即全身一阵"
               "刺痛，几股血柱自身上射出。\n$p陡然间一提真气，"
               "竟发现周身力道竟似涣散一般，全然无法控制。\n" NOR;
}

void poyuan_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                target->delete_condition("no_perform");
        }
        return;
}
