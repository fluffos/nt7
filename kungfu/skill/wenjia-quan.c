
// wenjia-quan 温家拳 (npc 功夫)

inherit SKILL;

mapping *action = ({
([     "action" : "$N一式「兔戏苍鹰」，侧身挥拳，带着呼呼的风声打向$n的$l",
       "force" : 180,
        "dodge" : 20,
        "parry" : -10,
       "lvl" : 0,       
       "damage_type" : "内伤"
]),
([     "action" : "$N左拳虚握，右拳快如闪电般打向$n的$l，正是一招「飞流直泻」",
       "force" : 205,
        "dodge" : 0,
       "lvl" : 0,
        "damage_type" : "瘀伤"
]),
([     "action" : "$N使招「风雨归人」，双拳交错，忽又分开，引内劲打向$n的$l",
       "force" : 340,
        "dodge" : -10,
        "parry" : 5,
       "lvl" : 10,
        "damage_type" : "内伤"
]),
([     "action" : "$N双拳犹如狂风骤雨般打向$n，拳影闪烁，已将$n团团围住",
       "force" : 380,
        "dodge" : 5,
        "parry" : 0,
       "lvl" : 10,
        "damage_type" : "瘀伤"
]),
([     "action" : "$N纵身越起直落在$n身后，双脚落地后双拳向后挥出，打向$n的后心。",
       "force" : 390,
        "dodge" : 10,
        "parry" : -5,
       "lvl" : 30,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("温家拳拳必须空手。\n");
      
       if ((int)me->query("max_neili") < 100)
               return notify_fail("你的内力太弱，无法练功。\n");
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
       level   = (int) me->query_skill("wenjia-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的内力不够练温家拳。\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}


