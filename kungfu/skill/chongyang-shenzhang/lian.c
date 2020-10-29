
/*
尹志平左剑平刺，右掌正击，同时左腿横扫而出，正是全真派中的「三连环」绝招。赵志敬高纵丈馀，
挥剑下削。尹志平长剑脱手，猛往对方掷去，跟著「嘿」的一声，双掌齐出。

杨过见这几招凌厉变幻，已非己之所知，不禁手心人全是冷汗，眼见赵志敬身在半空，一个势虚，一
个势实，看来这两掌要打得他筋折骨断。岂知赵志敬竟在这情势危急异常之际忽然空中翻身，急退寻
丈，轻轻巧巧的落了下来。
*/


#include <ansi.h>

inherit F_SSERVER;

string name() { return "连环三招"; }

int perform(object me, object target)
{
        int skill;
        string weapon;
        int damage;
        string *limb, type, result, str;
        int ap, dp, pp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("连环三招只能对战斗中的对手使用。\n");


        if( objectp(query_temp("weapon", me)) )
                return notify_fail("连环三招需空手才能施展！\n");

        if( me->query_skill_mapped("strike") != "chongyang-shenzhang" )
                return notify_fail("你所用的并非重阳神掌，不能施展连环三招！\n");

        if( me->query_skill_prepared("strike") != "chongyang-shenzhang" )
                return notify_fail("你所备的并非重阳神掌，不能施展连环三招！\n");

        //if( me->query_skill_mapped("force") != "xiantian-gong" )
        //        return notify_fail("你所用的并非玄门先天功，施展不出连环三招！\n");

        if( me->query_skill("force") < 120 )
                return notify_fail("你的内功火候未到，无法施展连环三招！\n");

        if( me->query_skill("strike") < 120 )
                return notify_fail("连环三招需要精湛的重阳神掌方能有效施展！\n");

        if( query("neili", me) <= 200 )
                return notify_fail("你的内力不够使用连环三招！\n");

        message_combatd(HIY "$N怒喝一声，拚尽全力，突然闪电般攻出指、掌、腿连环三招！\n\n" NOR, me, target);

        skill = me->query_skill("strike")/2 + me->query_skill("strike") / 8;

        addn_temp("apply/attack", skill, me);

        if( me->query_skill_prepared("strike") == "chongyang-shenzhang" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("strike");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        if( query_temp("restore", me))me->prepare_skill("strike","chongyang-shenzhang");

        if( me->query_skill_prepared("finger") == "zhongnan-zhi" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("finger");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        if( query_temp("restore", me))me->prepare_skill("finger","zhongnan-zhi");
        addn_temp("apply/attack", -skill, me);

        message_combatd( HIY "\n紧跟着$N突然腾空飞起，使出一招鸳鸯连环腿，两腿风驰电掣连环踢向$n\n" NOR,me,target);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        pp = defense_power(target, "parry");
        if( ap / 2 + random(ap) > dp )
        {
                if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
                {
                        message_combatd(HIR"只听$N一声惨叫，这连环二腿正中心口。但见$n一个身躯突然平平飞出，腾的一响，尘土飞扬，跌在丈许之外，直挺挺的躺在地下，再也不动。\n\n"NOR, target,target );
                        damage=query("eff_qi", target);
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage=query("qi", target);
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
                        addn("neili", -query("jiali", me), me);
                }
                else
                {
                        damage=damage_power(me, "strike");
                        addn("neili", -query("jiali", me), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", damage/2, me);

                        limb=query("limbs", target);
                        type = "瘀伤";
                        message_combatd("只听$N一声惨叫，这连环二腿正中$P"+limb[random(sizeof(limb))]+"，结果把$P踢摔了个跟头。\n",target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                }
                me->start_busy(1+random(2));
        }
        else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
        //else if( ap / 2 + random(ap) < pp )
        {
                message_combatd(HIR"$N猛觉得劲风罩来，心知不妙，慌忙闪开，结果$n踢了个空，白白自己重重跌了一跤。\n\n"NOR, target,me );
                me->start_busy(2+random(2));
        }
        else
        {
                message_combatd( "$N眼见这一腿来势凶猛，当下双足一点，跃高四尺，躲开了$n这一招，不过也出了一身冷汗。\n\n" NOR,  target,me);
                me->start_busy(2);
        }

        addn("neili", -random(me->query_skill("strike")/4)-100, me);

        return 1;
}
