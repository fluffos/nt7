// This program is a part of NITAN MudLIB
// yanzi-blade.c (燕子双飞刀法)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N一式" HIM "「秋燕双飞」" NOR "忽地放手，$w的尾端向上弹起，以意想不到方位呼的向$n$l砍去",
        "force"  : 120,
        "attack" : 40,
        "dodge"  : -30,
        "parry"  : -15,
        "lvl"    : 0,
        "damage" : 40,
        "damage_type" : "割伤",
        "skill_name"  : "秋燕双飞",
]),
([      "action" : "$N突然一声清啸，一招" HIR "「双燕回巢」" NOR "虚虚实实，是是而非的砍向$n的$l",
        "force"  : 150,
        "attack" : 45,
        "dodge"  : -40,
        "parry"  : -20,
        "lvl"    : 40,
        "damage" : 60,
        "damage_type" : "割伤",
        "skill_name"  : "双燕回巢",
]),
([      "action" : "不见$N如何动作，忽然来到$n右侧三尺许处," HIB "「空中燕舞」" NOR "抽出$w随手向$n的$l砍去",
        "force"  : 180,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -25,
        "lvl"    : 60,
        "damage" : 80,
        "damage_type" : "割伤",
        "skill_name"  : "空中燕舞",
]),
([      "action" : "$N手中的$w划出一个个的圈子，一招" HIW"「天方地园」" NOR"向$n的$l砍去",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -50,
        "parry"  : -30,
        "lvl"    : 80,
        "damage" : 95,
        "damage_type" : "割伤",
        "skill_name"  : "天方地园",
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
                return notify_fail("你的基本刀法不够，难以修炼燕子双飞刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("yanzi-blade", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的燕子双飞刀法。\n");

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
                return notify_fail("你的体力不够，练不了燕子双飞刀法。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的内力不够，练不了燕子双飞刀法。\n");

        me->receive_damage("qi", 64);
        addn("neili", -84, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yanzi-blade", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
        return __DIR__"yanzi-blade/" + action;
}