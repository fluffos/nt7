// SKILL liuyang-zhang.c

inherit SKILL;

mapping *action = ({
([        "action" : "$N一招「无对」，左掌叠于右掌之上，劈向$n",
        "force" : 130,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 0,
        "skill_name" : "无对",
        "damage_type" : "瘀伤"
]),
([        "action" : "$N一招「无双」，面色诡异，双掌轻飘飘地拍向$n",
        "force" : 150,
        "dodge" : 10,
        "damage" : 30,
        "lvl" : 20,
        "skill_name" : "无双",
        "damage_type" : "内伤"
]),
([        "action" : "$N一招「无拘」，双掌幻化一片幻影，将$n笼罩于内。",
        "force" : 150,
        "dodge" : 30,
        "damage" : 35,
        "lvl" : 30,
        "skill_name" : "无拘",
        "damage_type" : "瘀伤"
]),

([        "action" : "$N一招「无束」，向$n的$l连击三掌",
        "force" : 200,
        "dodge" : 25,
        "damage" : 50,
        "lvl" : 40,
        "skill_name" : "无束",
    "damage_type" : "瘀伤"
]),
([        "action" : "$N一招「无声」，只见一片掌影攻向$n",
        "force" : 250,
        "dodge" : 20,
        "damage" : 70,
        "lvl" : 40,
        "skill_name" : "无声",
        "damage_type" : "瘀伤"
]),

([        "action" : "$N双掌平挥，不见掌影,不闻掌风,一招「无息」击向$n",
        "force" : 300,
        "dodge" : 25,
        "damage" : 80,
        "lvl" : 60,
        "skill_name" : "无息",
            "damage_type" : "瘀伤"
]),
([        "action" : "$N一招「无影」，只见一片红影罩向$n",
        "force" : 350,
        "dodge" : 30,
        "damage" : 90,
        "lvl" : 70,
        "skill_name" : "无影",
        "damage_type" : "内伤"
]),

([        "action" : "$N左掌虚晃，右掌一记「无踪」击向$n的头部",
        "force" : 350,
        "dodge" : 50,
        "damage" : 120,
        "lvl" : 80,
        "skill_name" : "无踪",
           "damage_type" : "瘀伤"
]),

});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }
int valid_combine(string combo) { return combo=="dashou-yin"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练无影神拳必须空手。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练无影神拳。\n");

        return 1;
}

//mapping query_action(object me, object weapon)
//{
//        int i, level;
//        level = (int) me->query_skill("wuying-shenquan",1);
//        for(i = sizeof(action); i > 0; i--)
//                if(level > action[i-1]["lvl"])
//                        return action[NewRandom(i, 20, level/5)];
//}
/* ----------------
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
-------------------*/


mapping query_action(object me, object weapon)
{
        int i, level;
    level   = (int) me->query_skill("wuying-shenquan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够练无影神拳。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuying-shenquan/" + action;
}