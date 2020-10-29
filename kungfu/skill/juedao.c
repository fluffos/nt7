#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N深吸一口气，举起手中$w砍向$n，刀光在空中划出一道弧线",
        "force"  : 20,
        "attack" : 50,
        "dodge"  : 10,
        "parry"  : 30,
        "lvl"    : 0,
        "damage" : 30,
        "damage_type" : "砍伤",
]),
([      "action" : "$N反手一刀，刀光划向$n，姿势优美之极",
        "force"  : 40,
        "attack" : 65,
        "dodge"  : 10,
        "parry"  : 45,
        "lvl"    : 10,
        "damage" : 50,
        "damage_type" : "割伤",
]),
([      "action" : "$N从容不迫，转动着手中$w，渐渐将$n笼罩",
        "force"  : 80,
        "attack" : 80,
        "dodge"  : 10,
        "parry"  : 55,
        "lvl"    : 20,
        "damage" : 60,
        "damage_type" : "割伤",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("blade", 1) < 10 )
                return notify_fail("你的基本刀法水平有限，无法练习绝刀\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("juedao", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的绝刀\n");

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
      level = (int) me->query_skill("juedao", 1); 
      for (i = sizeof(action); i > 0; i--) 
              if (level > action[i-1]["lvl"]) 
                      return action[NewRandom(i, 20, level / 5)]; 
    
} 

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<20 )
                return notify_fail("你的体力不够，无法继续练习。\n");

        me->receive_damage("qi", 15);

        return 1;
}
