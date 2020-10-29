// po.c 破字诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int n;
        int skill, skill2, ap, dp, damage;
        string type;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("never-defeated", 1);

        skill2 = me->query_skill("martial-cognize", 1);

        if (! me->is_fighting(target))
                return notify_fail("破字诀只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须手持兵刃才能施展破字诀！\n");

        type=query("skill_type", weapon);
        if (me->query_skill(type, 1) < 150)
                return notify_fail("你的" + to_chinese(type) + "水平有限，无法施展破字诀！\n");

        if (me->query_skill_mapped(type) != "never-defeated")
                return notify_fail("你没有激发不败神功，无法施展破字诀！\n");

        if (me->query_skill_mapped("force") != "never-defeated") 
                return notify_fail("你现在没有激发不败神功为内功，难以施展破字诀。\n");                 

        if (skill < 100)
                return notify_fail("你的不败神功等级不够，无法施展破字诀！\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在真气不够！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -100, me);

        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        msg = HIC "$N" HIC "手中" + weapon->name() +
              HIC "一抖，犹如夜雨流星，铺天盖地的攻向$n"
              HIC "，没有半点规矩可循。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                n = 4 + random(4);
                if (ap * 2 / 3 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "见来招即巧又拙，不同于人间"
                               "任何招式，不禁大为慌乱，一时破绽迭出，$N"
                               HIY "见状连出" + chinese_number(n) + "招！\n" NOR;
                        message_combatd(msg, me, target);
                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
                                        target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        weapon2=query_temp("weapon", target);
                        if( weapon2 && random(ap)>dp && query("type", weapon2) != "pin" )
                        {
                                msg = HIW "$n" HIW "觉得眼前眼花缭乱，手中的" + weapon2->name() +
                                      HIW "一时竟然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "$n竭力抵挡，一时间再也无力反击。\n" NOR;
                        }

                        if (! me->is_fighting(target))
                                // Don't show the message
                                return 1;
                } else
                {
                        msg += HIY "$n" HIY "只办了个勉力遮挡，全然无法反击。\n" NOR;
                        target->start_busy(4 + random(skill / 30));
                }
        } else
        {
                msg += HIC "不过$n" HIC "一丝不苟，严守门户，没有露出半点破绽。\n" NOR;
                me->start_busy(3 + random(2));
        }

        message_combatd(msg, me, target);
        return 1;
}
