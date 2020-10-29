// chunyang-quan.c 纯阳拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int chunyangwuji(object me, object victim, object weapon, int damage);
mapping *action = ({
([        "action":
"只见$N身形一矮，大喝声中以拳化勾一个"HIW"「玄鹤捕食」"NOR"对准$n的$l戳了过去",
        "lvl" : 0,
        "skill_name" : "玄鹤捕食"
]),
([        "action":
"$N左手一分，身形扭转右拳运气，蜿蜒前伸，一招"HIY"「金蛇寻龟」"NOR"便往$n的$l
招呼过去",
        "lvl" : 20,
        "skill_name" : "金蛇寻龟"
]),
([        "action":
"$N右拳在$n面门一晃，和身向前一扑左拳使了个"HIB"「野马上槽」"NOR"往$n的$l狠命一抡",
        "lvl" : 40,
        "skill_name" : "野马上槽"
]),
([        "action":
"$N步履一沉，左拳拉开，右拳带风，一招"HIR"「黑虎掏心」"NOR"势不可挡地击向$n$l",
        "lvl" : 60,
        "skill_name" : "黑虎掏心"
]),
([        "action":
"只见$N拉开架式，一招"HIM"「二龙戏珠」"NOR"双拳齐出击向$n$l，虎虎有风",
        "lvl" : 80,
        "skill_name" : "二龙戏珠"
]),
([        "action":
"$N虚晃一拳，回身欲走，只霎那间身子一侧，反脚踢起，正是"RED"「麒麟反挂」"NOR"！",
        "lvl" : 100,
        "skill_name" : "麒麟反挂"
]),
([        "action":
"$N拉开后弓步，左拳一晃，右拳随出，左右拳掌交替变幻迭出，一招"GRN"「青龙
夺食」"NOR"往$n的$l攻去",
        "lvl" : 120,
        "skill_name" : "青龙夺食"
]),
([        "action":
"只见$N运足气力，一个纵身，右拳从左拳后侧身穿出，身随拳至，力势千钧！
这一招的名字叫作"HIR"「赤龙穿云」"NOR"",
        "lvl" : 140,
        "skill_name" : "赤龙穿云"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanhua-juding"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练纯阳拳必须空手。\n");
        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的内功火候不够，无法学纯阳拳。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练纯阳拳。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的内力不够练纯阳拳。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 200;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("chunyang-quan", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "内伤" : "瘀伤",
                //"post_action": (: chunyangwuji :),
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

void finish_chunyangwuji(object me, int skill_lvl)
{
        //set_temp("apply/attack",query_temp("cyq-wuji/old_attack",  me), me);
        //set_temp("apply/unarmed_damage",query_temp("cyq-wuji/old_damage",  me), me);
        delete_temp("perform/chunyangwuji", me);
        delete_temp("cyq-wuji", me);
        me->start_busy(2+random(2));
}
int chunyangwuji(object me, object victim, object weapon, int damage)
{
        string msg;
        int cyq_wuji=query_temp("perform/chunyangwuji", me);
        int skill_lvl = me->query_skill("chunyang-quan", 1)/4;
        int exp_m=query("combat_exp", me);
        int exp_t=query("combat_exp", victim);

        if( damage > 0 ) {
                if( query("qi", victim) <= 0){
                        msg = HIR"\n\t只见$N拳风威猛，当第"+chinese_number(cyq_wuji)+"招发出时，$n已经受不住$N的拳风！\n"NOR;
                        //if( me->is_killing(query("id", victim)) )
                                victim->receive_wound("qi",query("max_qi", victim),me);
                        message_combatd(msg , me, victim);
                        finish_chunyangwuji(me, skill_lvl);
                        return 1;
                }else msg = HIY"\n\t$N一招命中，不待$n反应第"+chinese_number(cyq_wuji+1)+"招已经以排山倒海之势向$n攻来！\n"NOR;
        }else{
                if( random(exp_m) < random(exp_t / 2) ){
                        msg = HIW"\n\t$N一招不中，顿时乱了自己的招数，纯阳无极的威猛招式再也使不出来！\n"NOR;
                        message_combatd(msg , me, victim);
                        finish_chunyangwuji(me, skill_lvl);
                        return 1;
                }else{
                        msg = HIY"\n\t$N一招不中，急转身形将第"+chinese_number(cyq_wuji+1)+"招迅速递出，速度较前快且发力更深！\n"NOR;
                        //addn_temp("apply/unarmed_damage", skill_lvl/3, me);
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                }
        }
        if( cyq_wuji >= query_temp("cyq-wuji/max_times", me)){
                msg = HIY"\n\t$N一口气向$n连续攻出"+chinese_number(cyq_wuji)+"招，纯阳拳的威力着实不可被轻视！\n"NOR;
                message_combatd(msg , me, victim);
                finish_chunyangwuji(me, skill_lvl);
                return 1;
        }

        addn_temp("perform/chunyangwuji", 1, me);
        //addn_temp("apply/attack", skill_lvl/2, me);
        //addn_temp("apply/unarmed_damage", -skill_lvl/2, me);
        message_combatd(msg , me, victim);
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"chunyang-quan/" + action;
}
int help(object me)
{
        write(HIC"\n纯阳拳："NOR"\n");
        write(@HELP

    纯阳拳为王重阳所创的全真派拳法。
    可与昊天掌互备。

        学习要求：
                先天气元功20级
                内力100
HELP
        );
        return 1;
}
