#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N手中$w忽地斜砍，嗡嗡作响，一式「天刀式」，袭向$n$l",
        "force"  :  20,
        "dodge"  :  28,
        "damage" :  15,
        "lvl"    :  0,
        "damage_type":  "砍伤",
        "skill_name"  : "天刀式",
]),
([      "action" :  "$N手中$w反转，踏步向前，一式「风刀式」，砍向$n$l",
        "force"  :  40,
        "dodge"  :  24,
        "damage" :  20,
        "lvl"    :  25,
        "damage_type":  "砍伤",
        "skill_name"  : "风刀式",
]),
([     
        "action" :  "$N怒喝一声，飞身跃起，一式「灭刀式」，$w嗡嗡两声，已到$n$l",
        "force"  :  60,
        "dodge"  :  24,
        "damage" :  18,
        "lvl"    :  50,
        "damage_type":  "砍伤",
        "skill_name"  : "灭刀式",
]),
([      
        "action" :  "$N手中$w坐砍右劈，一式「平刀式」，平平挥向$n",
        "force"  :  80, 
        "dodge"  :  30,
        "damage" :  25,
        "lvl"    :  75,
        "damage_type":  "砍伤",
        "skill_name"  : "平刀式",
]),
([      
        "action" : "$N将$w横于胸前，猛地劈出，一式「绝刀式」，砍向$n$l",
        "force"  :  100,
        "dodge"  :  38,
        "damage" :  35,
        "lvl"    :  100,
        "damage_type":  "砍伤",
        "skill_name"  : "绝刀式",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "blade" )
                return notify_fail("你必须先找一把刀才能练天绝刀法。\n");

            if( query("max_neili", me)<100 )
                return notify_fail("你目前的内力修为不够，没有办法练天绝刀法。\n");

            if (me->query_skill("blade", 1) < 15)
                return notify_fail("你的基本刀法火候太浅，没有办法练天绝刀法。\n");

            if (me->query_skill("blade", 1) < me->query_skill("tianjue-dao", 1))
                return notify_fail("你的基本刀法火候有限，无法领会更高深的天绝刀法。\n");

            return 1;
}

int valid_enable(string usage)
{
            return usage == "blade" || usage == "parry";
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

        level = (int) me->query_skill("tianjue-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
            object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<40 )
                       return notify_fail("你的内力不足，没有办法练天绝刀法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的体力不够练天绝刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianjue-dao/" + action;
}
