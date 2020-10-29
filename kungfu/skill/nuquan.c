// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N双目赤红，身带冲天杀气，招数缓慢凝重，一招「天地无光」似有千钧之力，缓缓朝$n的$l处拍去",
        "force" : 130,
        "dodge" : -20,
        "parry" : -20,
        "attack": 15,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "天地无光",
        "damage_type": "瘀伤"
]),
([      "action": "$N一声长啸．一招「毁天灭地」,一拳击出，有遇天开天，遇地破地之威攻向$n",
        "force" : 185,
        "dodge" : -25,
        "parry" : -25,
        "attack": 17,
        "damage": 43,
        "lvl"   : 20,
        "skill_name" : "毁天灭地",
        "damage_type":  "瘀伤"
]),
([      "action": "$N的手掌不断变换，一招「狂战四野」幻化出数个形状各异的掌形，顿时重重压力攻向$n！",
        "force" : 220,
        "dodge" : -31,
        "parry" : -33,
        "attack": 21,
        "damage": 68,
        "lvl"   : 40,
        "skill_name" : "狂战四野",
        "damage_type":  "内伤"
]),
([      "action": "$N立定身行，一招「同归洪荒」，右拳再猛地挥出，这一拳之威仿佛充满天地急速攻向$n！",
        "force" : 260,
        "dodge" : -71,
        "parry" : -83,
        "attack": 71,
        "damage": 88,
        "lvl"   : 90,
        "skill_name" : "同归洪荒",
        "damage_type":  "内伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练怒拳必须空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的内功火候不够，无法学怒拳。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练怒拳。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太浅。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("nuquan", 1))
                return notify_fail("你的基本拳法水平有限，无法领会更高深的怒拳。\n");

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
        level = (int) me->query_skill("nuquan", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练怒拳。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"nuquan/" + action;
}
