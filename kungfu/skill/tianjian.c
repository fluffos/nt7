#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N剑横于胸，猛地刺向$n，招式颇为凌厉",
        "force"  : 20,
         "attack" : 40,
        "dodge"  : 20,
        "parry"  : 20,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type": "刺伤"
]),
([      "action" : "$N手中$w在半空划出一个半圆，忽然间剑光一闪，$w已刺向$n$l",
        "force"  : 40,
        "attack" : 60,
        "dodge"  : 20,
        "damage" : 40,
        "lvl"    : 10,
        "damage_type": "刺伤"
]),
([      "action" : "$N飞身而起，只见半空剑闪动，$w犹如生了眼睛一般刺向$n",
        "force"  : 60,
        "attack" : 80,
        "dodge"  : 15,
        "damage" : 50,
        "lvl"    : 20,
        "damage_type": "刺伤"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("你的基本剑法火候太浅，无法学习天剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tianjian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的天剑。\n");

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
        level = (int) me->query_skill("tianjian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<10 )
                return notify_fail("你的体力不够练天剑。\n");

        me->receive_damage("qi", 5);        

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianjian/" + action;
}


void skill_improved(object me)   
{
        int lvl;

        lvl = me->query_skill("tianjian", 1);  
        if( lvl >= 30 &&  
            !query("can_perform/tianjian/lian", me) )   
        {
                tell_object(me, HIC "你通晓了天剑「" HIR "连环决" HIC "」的奥秘。\n" NOR);     
                set("can_perform/tianjian/lian", 1, me);  
        }
}

