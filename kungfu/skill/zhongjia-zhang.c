// zhongjia-zhang.c 钟家掌法
// NPC 专用

inherit SKILL;

mapping *action = ({
([     "action" : "$N纵身向前，掌势一发即收，双掌连晃，二掌直出，攻向$n的上中下三路",
       "force" : 150,
        "dodge" : 5,
       "damage_type" : "瘀伤",
       "lvl" : 0,
]),
([     "action" : "$N跃起丈余，在半空连转两个圈子，凌空挥掌，疾拍$n的胸前大穴",
       "force" : 160,
        "dodge" : 5,
        "damage_type" : "瘀伤",
       "lvl" : 12,
]),
([     "action" : "$N单臂画了个弧线，劈头盖脸地斩向$n的$l",
       "force" : 170,
        "dodge" : 5,
        "damage_type" : "劈伤",
       "lvl" : 18,
]),
([     "action" : "$N左掌护胸，立掌如剑，单手横劈，飕飕风响，猛地推向$n的$l",
       "force" : 185,
        "dodge" : -5,
        "damage_type" : "瘀伤",
       "lvl" : 24,
])
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("练钟家掌法必须空手。\n");
       if ((int)me->query_skill("jinglei-gong", 1) < 20)
               return notify_fail("你的惊雷功火候不够，无法学钟家掌法。\n");
       if ((int)me->query("max_neili") < 100)
               return notify_fail("你的内力太弱，无法练钟家掌法。\n");
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
       level = (int)me->query_skill("zhongjia-zhang", 1);
       for(i = sizeof(action); i > 0; i--)
               if(level > action[i-1]["lvl"])
                       return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的精力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的内力不够练钟家掌法。\n");
       me->receive_damage("jingli", 25);
       me->add("neili", -5);
       return 1;
}
