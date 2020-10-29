#include <ansi.h>
#include <combat.h>

#define HAI "「" HIG "苦海无边" NOR "」"

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
                return notify_fail(HAI "只能对战斗中的对手使用。\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "staff" )
                        return notify_fail("你手里拿的不是杖，怎么施展" HAI "？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "bluesea-force")
                        return notify_fail("你并没有准备使用南"
                                           "海玄功，如何施展" HAI "？\n");
        }

        if ((int)me->query_skill("bluesea-force", 1) < 260)
                return notify_fail("你的南海玄功不够娴熟，难以施展" HAI "。\n");

        if( query("max_neili", me)<3700 )
                return notify_fail("你的内力修为不足，难以施展" HAI "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不足，难以施展" HAI "。\n");
                
        if (weapon && me->query_skill_mapped("staff") != "bluesea-force")
                return notify_fail("你没有准备使用南海玄功，难以施展" HAI "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "bluesea-force")
                return notify_fail("你没有准备使用南海玄功，难以施展" HAI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        /*
        if (target->query_condition("no_exert"))
                return notify_fail("对方现在已经无法控制真气，放胆攻击吧。\n");
        */

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIB "$N" HIB "气贯双臂，向地一击，一股气浪卷着飞石如狂涛般袭向$n" HIB "，对方惊魂未定之际，忽闻三声轻响。\n"
              HIB "自$N" HIB "的" + name + HIB "中射出三道玄劲，分袭$n" HIB "三处死穴“云门穴、章门穴、哑门穴”。\n\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -500, me);
        } else
        {
                msg += CYN "$n" CYN "慌乱中一个鸽子翻身，跃出数丈，"
                       "侥幸躲开了这一招。\n" NOR;
                me->start_busy(3);
                addn("neili", -350, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_condition("no_exert")) return "";
        target->apply_condition("no_exert", 30);
        call_out("hai_end", 15 + random(ap / 20), me, target);
        return HIY "$n" HIY "只觉眼前飞沙走石，目不能视，忽觉身上要穴"
               "刺痛，三道血柱自身上射出。\n$p陡然间一提真气，"
               "竟觉得丹田之内空虚若谷，全然无法运气。\n" NOR;
}

void bian_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}