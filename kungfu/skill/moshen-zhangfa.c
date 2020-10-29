// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N右手冒出阵阵寒气，划了一个弧线朝$n的$l处打去",
        "force" : 10,
        "dodge" : 5,
        "parry" : 2,
        "lvl"   : 0,
        "skill_name" : "苍松迎客",
        "damage_type": "瘀伤"
]),
([      "action": "$N掌中的真气呈气劲，猛地朝$n的$l处击去",
        "force" : 15,
        "dodge" : 18,
        "parry" : 17,
        "lvl"   : 10,
        "skill_name" : "峰回路转",
        "damage_type": "瘀伤"
]),
([      "action": "$N手掌一翻，双手掌重叠，只见一股气劲朝$n的$l处激射过去",
        "force" : 15,
        "dodge" : 16,
        "parry" : 19,
        "lvl"   : 20,
        "skill_name" : "奇峰突现",
        "damage_type": "瘀伤"
]),
([      "action": "$N双掌平推，$n只觉得一股翻江倒海之力朝自己压来",
        "force" : 25,
        "dodge" : 24,
        "parry" : 21,
        "lvl"   : 30,
        "skill_name" : "漫天花舞",
        "damage_type": "瘀伤"
]),

});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练魔神掌法必须空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，无法学魔神掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练魔神掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("moshen-zhangfa", 1))
                return notify_fail("你的基本掌法火候不足，无法领会更高深的魔神掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("moshen-zhangfa", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-zhangfa/" + action;
}