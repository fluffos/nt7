// This program is a part of NITAN MudLIB
// longteng-daofa.c (龙腾刀法)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N身行晃动,猛地一招[龙战四方]砍向$n的$l！",
        "force"  : 120,
        "attack" : -40,
        "dodge"  : -30,
        "parry"  : 15,
        "lvl"    : 0,
        "damage" : 40,
        "damage_type" : "割伤",
        "skill_name"  : "龙战四方",
]),
([      "action" : "$N身行猛地向前一冲,脚下虚晃一扫,举刀一招[龙腾四海]向$n的$l砍去！",
        "force"  : 150,
        "attack" : 45,
        "dodge"  : -40,
        "parry"  : -20,
        "lvl"    : 40,
        "damage" : 60,
        "damage_type" : "割伤",
        "skill_name"  : "龙腾四海",
]),
([      "action" : "$N腾空越起,挥刀凌空砍下,正是一招[索命一刀]！",
        "force"  : 180,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -25,
        "lvl"    : 60,
        "damage" : 80,
        "damage_type" : "割伤",
        "skill_name"  : "索命一刀",
]),
([      "action" : "$N大喝一声,一招[龙飞九天]连环朝$n的$l砍去！",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -50,
        "parry"  : -30,
        "lvl"    : 80,
        "damage" : 95,
        "damage_type" : "割伤",
        "skill_name"  : "龙飞九天",
]),
});

int valid_enable(string usage){ return usage == "blade" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < 120)
                return notify_fail("你的基本刀法不够，难以修炼龙腾刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("longteng-daofa", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的龙腾刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够，练不了龙腾刀法。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的内力不够，练不了龙腾刀法。\n");

        me->receive_damage("qi", 64);
        addn("neili", -84, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("longteng-daofa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
        return __DIR__"longteng-daofa/" + action;
}