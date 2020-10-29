// moke-zhi.c -摩诃指

inherit SKILL;

mapping *action = ({
([        "action" : "$N左指挥出，一式「叶不归根」，削向$n的掌缘",
        "force" : 100,
        "dodge" : 5,
        "lvl" : 0,
        "skill_name" : "叶不归根",
        "damage_type" : "刺伤"
]),
([        "action" : "$N全身之力聚于一指，一式「我心向佛」，指向$n的胸前",
        "force" : 140,
        "dodge" : 10,
        "lvl" : 15,
        "skill_name" : "我心向佛",
        "damage_type" : "刺伤"
]),
([        "action" : "$N左掌贴于神道穴，右手一式「以慈度心」，向$n的$l划过",
        "force" : 180,
        "dodge" : 15,
        "lvl" : 25,   
        "skill_name" : "以慈渡心",
        "damage_type" : "刺伤"
]),
([        "action" : "$N双目怒视，一式「三入地狱」，双指拂向$n的额、颈、肩、臂、胸、背",
        "force" : 220,
        "dodge" : 20,
        "lvl" : 45,
        "skill_name" : "三入地狱",
        "damage_type" : "刺伤"
]),
([        "action" : "$N一式「天衣无缝」，左掌掌心向外，右指蓄势点向$n的$l",
        "force" : 260,
        "dodge" : 25,
        "lvl" : 60,
        "skill_name" : "天衣无缝",
        "damage_type" : "刺伤"
]),
([        "action" : "$N右手伸出，十指叉开，一式「念经诵佛」，小指拂向$n的太渊穴",
        "force" : 330,
        "dodge" : 30,
        "lvl" : 70,
        "skill_name" : "念经送佛",
        "damage_type" : "刺伤"
]),
([        "action" : "$N双迸出无数道劲气，一式「我佛慈悲」射向$n的全身",
        "force" : 400,
        "dodge" : 35,
        "lvl" : 80,
        "skill_name" : "我佛慈悲",
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="jimie-zhua"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练摩诃指必须空手。\n");

         if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练摩诃指。\n");

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
        level   = (int) me->query_skill("mohe-zhi",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("jingli", me)<30 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够练摩诃指。\n");
        addn("jingli", -30, me);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
    return __DIR__"mohe-zhi/" + action;
}