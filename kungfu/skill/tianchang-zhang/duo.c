// duo.c 空手夺白刃

#include <ansi.h>

inherit F_SSERVER;

string name() { return "空手夺白刃"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill;
        int comb1,comb2;
        mixed exp1, exp2;
        int skill1,skill2,neili1,neili2,str1,str2;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("tianchang-zhang",1);

        if( !(me->is_fighting() ))
                return notify_fail("空手夺白刃只能对战斗中的对手使用。\n");

        if( objectp(weapon2=query_temp("weapon", me)) )
                return notify_fail("你必须空手。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("对方没有兵刃，你不用担心。\n");

        if( skill < 100)
                return notify_fail("你的天长掌法等级不够, 不能使用空手夺白刃！\n");

        if ((int)me->query_skill("lengyue-shengong", 1)<100)
                return notify_fail("你的冷月神功火候不够。\n");

        if ( me->query_skill_mapped("force") != "lengyue-shengong")
                return notify_fail("你没有运用冷月神功！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不够，无法使用空手折梅！\n");

        if( !living(target))
                return notify_fail("对方都已经这样了，还夺什么，去捡好了！\n");

        message_combatd(CYN"\n$N闪电般伸出右手，瞅准$n武功破绽之处，抓向$n手中的"+query("name", weapon)+CYN"。\n\n"NOR,me,target);

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);
        skill1 = me->query_skill("tianchang-zhang");
        skill2 = target->query_skill("parry");
        neili1=query("neili", me);
        neili2=query("neili", target);
        str1 = me->query_str();
        str2 = target->query_str();

        if (exp1 < exp2/3)
        {
                message_combatd("谁知$n露出此破绽乃是诱敌，一个变招反而向$N猛攻而至。\n",me,target);
                me->start_busy(1+random(3));
                addn("neili", -50, me);
                COMBAT_D->do_attack(target,me,query_temp("weapon", me));
                return 1;
        }

        if (exp1/ 100 > random(exp2/ 100))
        {
                message_combatd(HIR"$n眼睛一花，手中"+query("name", weapon)+HIR"已被$N反手抓到。\n\n"NOR,me,target);
                comb1 = str1*neili1*skill1;
                comb2 = str2*neili2*skill2;

                if (comb1 > comb2 * 3/5 )
                {
                        message_combatd(HIW"$n只觉一股寒气自"+query("name", weapon)+HIW"传了过来，整个手臂一阵冰凉，手中"+query("name", weapon)+HIW"脱手而出！\n"NOR,me,target);
                        weapon->unequip();
                        weapon->move(me);
                        addn("neili", -50, me);
                        return 1;
                }
                message_combatd(HIW"$N默运冷月寒气，催动寒冷真气注入"+query("name", weapon)+HIW"，$n见状赶紧催动体内真气与其相抗。\n\n"NOR,me,target);
                message_combatd(HIG"$N只觉$n手中的"+query("name", weapon)+HIG"传来一阵炎热的气劲，将自己的冷月寒气消弭于无形，只好放手，飘身退开。\n"NOR,me,target);
                me->start_busy(1+random(2));
                addn("neili", -150, me);
                return 1;

        }
        message_combatd("可是$n的看破了$N的企图，立刻采取守势，飘身躲开$N的攻击。\n",me,target);
        addn("neili", -50, me);
        me->start_busy(1+random(2));
        return 1;
}