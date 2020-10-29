// biluo-zhang.c 碧罗掌
// Last Modified by sir 10.23.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N一式「起手式」，左手带风，右手拍向$n的$l",
        "force"  : 30,
        "attack" : 5,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 10,
        "lvl"    : 0,
        "damage_type" : "瘀伤",
        "skill_name"  : "起手式"
]),
([      "action" : "$N右手微台，直出向前，一式「截手式」，疾向$n的$l击去",
        "force"  : 45,
        "attack" : 8,
        "dodge"  : 20,
        "parry"  : 35,
        "damage" : 13,
        "lvl"    : 10,
        "damage_type" : "瘀伤",
        "skill_name"  : "截手式"
]),
([      "action" : "$N使一式「逆风式」，左掌微拂，右掌顺势而进，猛地插往$n的$l",
        "force"  : 60,
        "attack" : 12,
        "dodge"  : 25,
        "parry"  : 20,
        "damage" : 15,
        "lvl"    : 25,
        "damage_type" : "瘀伤",
        "skill_name"  : "逆风式"
]),
([      "action" : "$N双掌隐隐泛出青气，一式「御气式」，掌风激劲，雨点般向$n击去",
        "force"  : 76,
        "attack" : 15,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 18,
        "lvl"    : 38,
        "damage_type" : "瘀伤",
        "skill_name"  : "御气式"
]),
([      "action" : "$N双掌不断反转，使出一式「潜手式」，双掌并拢，笔直地向$n的$l袭去",
        "force"  : 52,
        "attack" : 18,
        "dodge"  : 33,
        "parry"  : 30,
        "damage" : 25,
        "lvl"    : 55,
        "damage_type" : "瘀伤",
        "skill_name"  : "潜手式"
]),
([      "action" : "$N身形一变，使一式「齐掌式」，双掌带着萧刹的劲气，猛地击往$n的$l",
        "force"  : 90,
        "attack" : 20,
        "dodge"  : 38,
        "parry"  : 35,
        "damage" : 30,
        "lvl"    : 65,
        "damage_type" : "瘀伤",
        "skill_name"  : "齐掌式"
]),
([      "action" : "$N使一式「青烟式」，双掌如梦似幻，同时向$n的$l击去",
        "force"  : 120,
        "attack" : 22,
        "dodge"  : 42,
        "parry"  : 38,
        "damage" : 33,
        "lvl"    : 72,
        "damage_type" : "瘀伤",
        "skill_name"  : "青烟式"
]),
([      "action" : "$N一式「流云式」，身法忽变，似流云飘忽，不觉已击到$n的$l上",
        "force"  : 140,
        "attack" : 24,
        "dodge"  : 45,
        "parry"  : 45,
        "damage" : 38,
        "lvl"    : 80,
        "damage_type" : "瘀伤",
        "skill_name"  : "流云式"
]),
([      "action" : "$N突地一招「风雷式」，双掌挟着一阵风雷之势，猛地劈往$n的$l",
        "force"  : 160,
        "attack" : 26,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 50,
        "lvl"    : 90,
        "damage_type" : "瘀伤",
        "skill_name"  : "风雷式"
]),
});

int valid_enable(string usage) { return usage=="parry" || usage=="strike"; }
//int valid_combine(string combo) { return combo=="luoyan-hand"; }
int valid_combine(string combo)
{
        return combo == "henshan-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练碧罗掌法必须空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，无法学碧罗掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法碧罗掌法。\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("你的基本掌法火候太浅。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("biluo-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的碧罗掌法。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练碧罗掌。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
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
        int d_e1 = 15;
        int d_e2 = 50;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 30;
        int f_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("biluo-zhang", 1);
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
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"biluo-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n碧罗掌："NOR"\n");
        write(@HELP

    碧罗掌是衡山派的掌法。
    可与大落雁手互备。

        学习要求：
                回雁心法15级
                内力50
HELP
        );
        return 1;
}
