// This program is a part of NITAN MudLIB
// mang.c 剑芒


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "剑芒"; }
string *name1 = ({
        "玉堂穴",
        "大横穴",
        "幽门穴",
        "章门穴",
        "晴明穴",
        "紫宫穴",
        "风池穴",
        "百汇穴",
        "太阳穴",
        "长强穴",
        "灵台穴"
});

void check_fight(object me, object target, int amount);

int perform(object me, object target)
{
        string msg, name, name2;
        int ap, dp;
        object weapon=query_temp("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_fighting(me))
                return notify_fail("「剑芒」只能对战斗中的对手使用。\n");

        if( query("qi", target) <= 50 )
                return notify_fail("你现在没有必要用「剑芒」攻击敌人了。\n");

        if( !weapon || query("skill_type", weapon) != "sword"
        ||  me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你现在无法使用「剑芒」攻击敌人。\n");

        if( query_temp("perform", me) == 1 ||
            query_temp("perform2", me) == 1 ||
            query_temp("perform3", me) == 1 )
                return notify_fail("你现在正用着「剑芒」呢。\n");

        if ((int)me->query_skill("huashan-sword", 1) < 100 ||
            (int)me->query_skill("sword", 1) < 100 ||
            (int)me->query_str() < 25   ||
            (int)me->query_dex() < 25)
                return notify_fail("你有的功夫还不够娴熟，不会使用「剑芒」。\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 80)
                return notify_fail("你的紫霞神功修为不够，无法领悟「剑芒」的精髓。\n");


        if( query("max_neili", me)<800 )
                return notify_fail("你的内力太弱，无法使用出「剑芒」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

        name = name1[random(sizeof(name1))];
        name2=query("name", weapon);

        msg = HIC "\n$N右手剑锋一转，手中" + name2 + HIC "直斗，顿时使$N" +
              HIC "被一片剑辉所笼罩，其中一支剑芒奔向$n " HIC "的" + name + "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果一剑刺中，$n只觉得全身气脉通道阻塞，真气立受干挠！\n"NOR;
                if (! target->is_busy())
                        target->start_busy(2 + random(4));
                addn("neili", -200, me);
                set_temp("perform", 1, me);

                if ((int)me->query_skill("huashan-sword", 1) > 120
                && query("neili", me)>300 )
                {
                        call_out("perform2", 0, me , target);
                } else
                {
                        delete_temp("perform", me);
                }
        } else
        {
                me->start_busy(2);
                addn("neili", -100, me);
                addn("neili", -100, target);
                msg += HIY"\n$p大叫一声不好，全身用力一纵，顺势跳了开去。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_call_out((: call_other, __FILE__, "check_fight",
                           me ,target :), 1);
        return 1;
}

int perform2(object me, object target)
{
        string msg, name, name2;
        int damage, ap, dp;
        object weapon;

        if (! me) return 0;
        weapon=query_temp("weapon", me);

        if (! weapon)
        {
                me->start_call_out((: call_other, __FILE__, "check_fight",
                                   me ,target :), 1);
                return 1;
        }
        name2=query("name", weapon);

        if (! target) target = offensive_target(me);
        if (! target)
        {
                call_out("back", 3, me);
                return 1;
        }

        name = name1[random(sizeof(name1))];
        msg = MAG "\n接着$N踏前一步，" + name2 + "发出的第二支剑芒隔空点向$n的" + name + "，认穴竟无厘毫之差！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                delete_temp("perform", me);
                damage = damage_power(me, "sword");

                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "结果只听见$n" HIR "一声惨嚎，" + name2 + HIR "已在$p的" + name +
                                           HIR "对穿而出，鲜血溅得满地！！\n" NOR);

                if( !target->is_busy() )
                        target->start_busy(2);

                if ((int)me->query_skill("huashan-sword", 1) > 140
                && query("neili", me)>300 )
                {
                        call_out("perform3", 0, me ,target);
                } else
                {
                        delete_temp("perform2", me);
                }
        } else
        {       me->start_busy(3);
                addn("neili", -100, me);
                delete_temp("perform", me);
                msg += HIY"可是$p一个巧云翻身，远远的躲了开去。\n"NOR;
        }
        message_combatd(msg, me, target);
        me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
        return 1;
}

int perform3(object me, object target)
{
        int skill, j, ap, dp;
        string msg, name, name2;
        object weapon;

        if( !me || !weapon=query_temp("weapon", me) )
        {
                me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
                return 1;
        }
        name2=query("name", weapon);
        skill = (int)me->query_skill("huashan-sword", 1);
        skill = skill / 15;

        if (! target) target = offensive_target(me);
        if (! target)
        {
                call_out("back", 3, me);
                return 1;
        }

        name = name1[random(sizeof(name1))];
        msg = HIW "\n紧跟着$N手中" + name2 + "发出第三支剑芒，只见一道光芒直奔$n，剑辉扫向$n的" + name + "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                delete_temp("perform2", me);

                msg += HIR "$n只觉体内奇经八脉中内息为之一怠，全身气力竟然提不起来了！\n" NOR;
                msg += HIW "$N趁$n身形一慢的当儿，连环数剑奋力击出，正是剑宗绝技" + HIR "“夺命三仙剑”！\n" NOR;
                message_combatd(msg, me, target);
                addn("apply/attack", skill, me);
                addn("apply/damage", skill, me);

                for(j=0;j<(3+query("str", me)/10);j++ )
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

                addn("apply/attack", -skill, me);
                addn("apply/damage", -skill, me);

                if( !target->is_busy() )
                        target->start_busy(4);
                me->start_busy(3);
                addn("neili", -500, target);
                call_out("back", 3 + skill, me);

        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                delete_temp("perform2", me);
                target->start_busy(1);
                msg += HIY"\n$p喘息未定，见$P手中发出的剑芒如狂风般点来，连忙又跃开数尺，狼狈地避开。\n" NOR;
                message_combatd(msg, me, target);
        }
        me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
        return 1;
}

void back(object me)
{
        string msg;
        if (! me) return;
        msg = HIW "\n你身形一收，手中剑芒渐渐消失。\n" NOR;
        tell_object(me, msg);
        delete_temp("perform", me);
        delete_temp("perform2", me);
        delete_temp("perform3", me);
}

void check_fight(object me, object target, int amount)
{
        object weapon, where;
        if ( target )
        {
                where = environment(target);
                if ( !present(target,where) )
                {
                        if( query("qi", target) <= 50 && me->is_fighting(target) )
                        {
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                        }
                        else
                        if( !objectp(weapon=query_temp("weapon", me) )
                         || query("skill_type", weapon) != "sword"
                        || me->query_skill_mapped("sword") != "huashan-sword")
                        {
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                        }
                        else
                        if( !present(query("id", target),environment(me) )
                        || !target->is_fighting() || !me->is_fighting() || !living(target)
                        || !living(me) || target->is_ghost() || me->is_ghost() )
                        {
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                        }
                        else call_out("check_fight", 1, me, target, amount);
                } else
                {
                        delete_temp("perform", me);
                        delete_temp("perform2", me);
                        delete_temp("perform3", me);
                }
        }

}

