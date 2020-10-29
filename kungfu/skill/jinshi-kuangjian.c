// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N身行不住的飘动，手中$w幻起道道寒光，一招「狮啸苍天」刺向$n",
        "force" : 126,
        "parry" : -3,
        "dodge" : -5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "狮啸苍天",
        "damage_type":  "刺伤"
]),
([      "action": "$N身行突然变了数个变化，手中$w也随之变化，一招「金狮裂地」刺向$n的$l",
        "force" : 149,
        "parry" : -13,
        "dodge" : -10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "金狮裂地",
        "damage_type":  "割伤"
]),
([      "action": "$N抽身后退，一招「王者无情」,$w向波浪般的刺向$n的致命之处",
        "force" : 167,
        "parry" : -12,
        "dodge" : -15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "王者无情",
        "damage_type":  "刺伤"
]),
([      "action": "$N身行忽坐忽右，手中$w忽上忽下，一招「狮王怒吼」攻向$n的$l",
        "force" : 187,
        "parry" : -23,
        "dodge" : -19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "狮王怒吼",
        "damage_type":  "割伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，不能学习金狮狂剑。\n");

        if (me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本剑法火候不够，不能学习金狮狂剑。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不够，不能学习金狮狂剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshi-kuangjian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的金狮狂剑。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jinshi-kuangjian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够练金狮狂剑。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练金狮狂剑。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinshi-kuangjian/" + action;
}
