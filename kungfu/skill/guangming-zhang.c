// This program is a part of NT MudLIB
// guangming-zhang.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N双掌一错，一招“魔火天焚”幻出漫天掌影拢向$n的$l",
        "force" : 100,
        "dodge" : 5,
        "parry" : 1,
        "lvl" : 0,
        "damage" : 20,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出一招「圣火小天罗式」，右掌穿出击向$n的$l",
        "force" : 120,
        "dodge" : -2,
        "parry" : 2,
        "lvl" : 10,
        "damage" : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出一招「圣火大天罗式」，左掌化虚为实击向$n的$l",
        "force" : 140,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 20,
        "damage" : 40,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出光明神掌「圣火九转式」，如鬼魅般欺至$n身前，一掌拍向$n的$l",
        "force" : 160,
        "dodge" : -5,
        "parry" : -1,
        "lvl" : 30,
        "damage" : 40,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌一错，使出「圣火三连飞」，对准$n的$l连续拍出三掌",
        "force" : 180,
        "dodge" : -3,
        "parry" : 2,
        "lvl" : 40,
        "damage" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左掌画了个圈圈，右掌推出，一招「焰卷五方鼓」击向$n$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -3,
        "lvl" : 50,
        "damage" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" :"$N使出「风雷七星断」，身形散作七处同时向$n的$l出掌攻击",
        "force" : 220,
        "dodge" : 1,
        "parry" : 1,
        "lvl" : 60,
        "damage" : 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N吐气扬声，一招「气撼九重天」双掌并力推出",
        "force" : 250,
        "dodge" : 4,
        "parry" : -1,
        "lvl" : 70,
        "damage" : 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左掌画了个圈圈，右掌推出，一招「光明镇四方」击向$n$l",
        "force" : 280,
        "dodge" : 3,
        "parry" : 2,
        "lvl" : 80,
        "damage" : 70,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="shenghuo-quan"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("练光明神掌必须空手。\n");

        if ((int)me->query_skill("strike", 1) < 10)
                return notify_fail("你的基本掌法火候不够，无法练光明神掌。\n");


        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guangming-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的光明神掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("guangming-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 60)
                return notify_fail("你的体力太低了。\n");

        if ((int)query("neili", me) < 70)
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 20);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guangming-zhang/" + action;
}