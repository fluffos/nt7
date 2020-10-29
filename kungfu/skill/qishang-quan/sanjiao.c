// This program is a part of NT MudLIB
// sanjiao.c 三焦齐逆诀

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR "三焦齐逆诀"; }

int perform(object me,object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, neili_wound, qi_wound;
        int flag;
        int damage;
        string fskill,bskill,pskill,sskill;


        if( !objectp(target) )
        {
                flag =1;
                target = offensive_target(me);
        }

        if( !target || !target->is_character() || target == me ||
            !me->is_fighting(target) ||
            !living(target) )
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if (objectp(weapon = query_temp("weapon", me)))
                return notify_fail("你必须空手才能使用「三焦齐逆诀」。\n");

        fskill = "jiuyang-shengong";
        sskill = "qishang-quan";
        bskill = "cuff";

        if( (int)me->query_skill(fskill, 1) < 200 )
                return notify_fail("你的"+to_chinese(fskill)+"修为不足，不能随便使用"+name()+"。\n");

        if( (int)me->query_skill(sskill, 1) < 200 )
                return notify_fail("你的"+to_chinese(sskill)+"的修为不够，不能够体会"+name()+"。\n");

        if( (int)me->query_skill(bskill, 1) < 200 )
                return notify_fail("你的"+to_chinese(bskill)+"还不到家，无法体现七伤拳的"+name()+"。\n");

        if( (int)query("neili", me) < 2000 )
                return notify_fail("你的内力还不够高！\n");

        skill = me->query_skill(bskill,1) + me->query_skill("force",1);

        msg = HIY"$N凝神定气，企图使出七伤拳总诀中的「" HIR "三焦齐逆诀" HIY "」，将敌方招数反弹！\n"NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -500, me);

                msg += HIG "$n只觉得胸前一阵剧痛，“哇”的一声喷出一口鲜血！\n"NOR;
                neili_wound = damage_power(me, "cuff");
                damage+= query("jiali", me);
                qi_wound = neili_wound ;
                if(qi_wound > query("qi", target))
                        qi_wound = query("qi", target);
                target->receive_wound("qi", qi_wound,me);

                if(neili_wound > query("neili", target))
                        neili_wound = query("neili", target);
                addn("neili", -neili_wound, target);
                if( !target->is_busy() )
                        target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg+=HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;
                addn("neili", -200, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

