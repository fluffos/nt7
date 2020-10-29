// This program is a part of NITAN MudLIB
// duo.c 空手入白刃

#include <ansi.h>

inherit F_SSERVER;

string name() { return "空手入白刃"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int ap, dp, skill;
        int fmsk = me->query_skill("fanlao-huantong", 1)+me->query_skill("xiaoyao-you", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("zhemei-shou", 1);

        if (! me->is_fighting())
                return notify_fail("空手入白刃只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须空手。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("对方没有兵刃，你不用担心。\n");

        if (skill < 50)
                return notify_fail("你的天山折梅手等级不够, 不能空手入白刃！\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 50 &&
            (int)me->query_skill("xiaowuxiang", 1) < 80 &&
            (int)me->query_skill("beiming-shengong", 1) < 50)
                return notify_fail(RED"你本门内功火候不够，使不出「空手夺白刃」。\n"NOR);

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够，无法空手入白刃！\n");

        msg = CYN "$N凝神闭息，打算施展空手入白刃的绝技. \n";
        message_combatd(msg, me, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");
        
        ap += fmsk;
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg = "$N使出空手入白刃的绝招, $n顿时觉得眼前一花，手腕一麻，手中兵刃脱手而出！\n" NOR;
                weapon2->move(me);
                if (weapon2->is_item_make() && random(2))
                {
                        weapon2->move(target);
                        msg += "那可是$n的随身家伙！$n手一伸将它夺回来。\n" NOR;
                }
                me->start_busy(2);
        }
        else
        {
                msg = "可是$p的看破了$P的企图，立刻采取守势，使$P没能夺下兵刃。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
