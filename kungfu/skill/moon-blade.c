// This program is a part of NITAN MudLIB
// moon-blade.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N挥舞$w，使出一招「圆月当空」，上劈下撩，左挡右开，齐齐罩向$n",
        "skill_name" : "圆月当空",
        "force"  : 120,
        "attack" : 35,
        "dodge"  : -30,
        "parry"  : -32,
        "lvl"    : 0,
        "damage" : 240,
        "damage_type" : "割伤",
        "skill_name"  : "圆月当空",
]),
([      "action" : "$N展身虚步，提腰跃落，一招「云遮雾扰」，刀锋一卷，拦腰斩向$n",
        "skill_name" : "云遮雾扰",
        "force"  : 160,
        "attack" : 42,
        "dodge"  : -40,
        "parry"  : -45,
        "lvl"    : 30,
        "damage" : 250,
        "damage_type" : "割伤",
        "skill_name"  : "云遮雾扰",
]),
([      "action" : "$N手中$w一抖，一招「拨云见月」，手中$w化成一道银练，攻向$n的$l",
        "skill_name" : "拨云见月",
        "force"  : 185,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -47,
        "lvl"    : 50,
        "damage" : 260,
        "damage_type" : "割伤",
        "skill_name"  : "拨云见月",
]),
([      "action" : "$N神态悠闲，手中$w触地，一招「对影三人」从不可思议的角度划向$n的$l",
        "skill_name" : "对影三人",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -55,
        "parry"  : -61,
        "lvl"    : 80,
        "damage" : 270,
        "damage_type" : "割伤",
        "skill_name"  : "对影三人",
]),
([      "action" : "$N手中$w手中$w不停地颤抖着，剑气不断的发出，这招「花前月下」齐齐罩向$n",
        "skill_name" : "花前月下",
        "force"  : 255,
        "attack" : 65,
        "dodge"  : -60,
        "parry"  : -72,
        "lvl"    : 100,
        "damage" : 280,
        "damage_type" : "割伤",
        "skill_name"  : "花前月下",
]),
([      "action" : "$N手中$w如同流星暴雨，毫不停歇地朝$n砍去，正是一招「常娥奔月」",
        "skill_name" : "常娥奔月",
        "force"  : 290,
        "attack" : 70,
        "dodge"  : -70,
        "parry"  : -75,
        "lvl"    : 120,
        "damage" : 290,
        "damage_type" : "割伤",
        "skill_name"  : "常娥奔月",
]),
([      "action" : "$N手中的$w带起一阵狂风，顿时无数朵刀花夹带着风雷之声一招「刀光月影」朝$n的$l处砍去",
        "skill_name" : "刀光月影",
        "force"  : 320,
        "attack" : 80,
        "dodge"  :- 85,
        "parry"  : -85,
        "lvl"    : 140,
        "damage" : 300,
        "damage_type" : "割伤",
        "skill_name"  : "刀光月影",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( query("con", me)<26 )
                return notify_fail("你研究了半天，只觉得根骨有些差，始终无法理解其中的真谛。\n");

        if( query("int", me)<30 )
                return notify_fail("你研究了半天，只觉得悟性有些差，始终无法理解其中的真谛。\n");

        if( query("str", me)<26 )
                return notify_fail("你研究了半天，感觉膂力有些低，始终无法随意施展。\n");

        if( query("dex", me)<39 )
                return notify_fail("你研究了半天，只觉依自己的身法灵动性，根本无法修习这门武功。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("你的内功火候太浅。\n");

        weapon=query_temp("weapon", me);
        if (me->query_skill("moon-blade", 1) < 600 &&
              (!objectp(weapon) || query("id", weapon) != "moon blade") )
                return notify_fail("你的圆月刀法大成之前必须有圆月弯刀配合才能学习。\n");

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
        level   = (int) me->query_skill("moon-blade", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        return notify_fail("圆月刀法博大精深，无法靠着普通的练习提升。\n");
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够，练不了圆月弯刀。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够，练不了圆月弯刀。\n");

        if (! present("moon blade", me) && me->query_skill("moon-blade") < 400)
                return notify_fail("你的圆月刀法大成之前必须有圆月弯刀配合才能练习。\n");

        me->receive_damage("qi", 55);
        addn("neili", -61, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str() / 10)
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "$N" HIW "仰天一啸，刀劲迸发，满天具是雪亮的刀光，犹如满月的月光般美丽，\n"
                                     "但却让人感到落入森罗地狱般，全身止不住的战抖，\n"
                                     HIR "霎时一股冰寒的刀气掠过$n" HIR "全身，$n" HIR "全身顿时鲜血淋漓，摇摇欲倒。\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"moon-blade/" + action;
}
