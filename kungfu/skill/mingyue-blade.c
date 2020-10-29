// This program is a part of NITAN MudLIB
// mingyue-blade.c (天涯明月刀)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N身形沉稳，手中$w猛的一转，施展出单刀的刀法，一招「举杯邀明月」朝$n的$l处砍去！",
        "force"  : 120,
        "attack" : 35,
        "dodge"  : -30,
        "parry"  : -12,
        "lvl"    : 0,
        "damage" : 240,
        "damage_type" : "割伤",
        "skill_name"  : "举杯邀明月",
]),
([      "action" : "$N刀锋一转，划过一道圆弧，突然又于其上施展出挑、刺的招数，正是一招「对影成三人」！",
        "force"  : 160,
        "attack" : 42,
        "dodge"  : -40,
        "parry"  : -15,
        "lvl"    : 40,
        "damage" : 250,
        "damage_type" : "割伤",
        "skill_name"  : "对影成三人",
]),
([      "action" : "$N刀法突然凌厉，专走险路，赫然竟是马刀的路数，只见一招「天涯共此时」朝$n的$l砍去！",
        "force"  : 185,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -17,
        "lvl"    : 60,
        "damage" : 260,
        "damage_type" : "割伤",
        "skill_name"  : "天涯共此时",
]),
([      "action" : "$N体内的真气在不断变化，不断游移，突然一招「海角若比邻」斩向$n的$l!",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -55,
        "parry"  : -21,
        "lvl"    : 80,
        "damage" : 270,
        "damage_type" : "割伤",
        "skill_name"  : "海角若比邻",
]),
});

int valid_enable(string usage){ return usage == "blade" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < 140)
                return notify_fail("你的基本刀法不够，难以修炼天涯明月刀。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("mingyue-blade", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的天涯明月刀。\n");

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
        level   = (int) me->query_skill("mingyue-blade", 1);
        if (random(me->query_skill("blade")) > 180
        &&  me->query_skill("force") > 200
         && query("neili", me)>1000
         && objectp(weapon=query_temp("weapon", me)) )
        {
                addn("neili", -300, me);
                return ([
                        "action": "$N使出一招" HIM "「天涯明月相思泪」" NOR "，$w霍地射出寒光点点，犹如冬夜寒雨般铺天盖地扫向$n",
                        "damage": 500,
                        "dodge" : -100,
                        "parry" : -150,
                        "attack": 150,
                        "damage_type": "割伤"
                ]);
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够，练不了天涯明月刀。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的内力不够，练不了天涯明月刀。\n");

        me->receive_damage("qi", 64);
        addn("neili", -84, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        int lvl = me->query_skill("mingyue-blade", 1);
        weapon=query_temp("weapon", me);

        if (lvl < 180 || lvl / 2 + random(lvl) < (int)victim->query_skill("dodge", 1) ||
            query("neili", me)<500 ||
            me->query_skill("dodge", 1) < 180 ||
            me->query_skill("force", 1) < 150 ||
            victim->is_busy() )
                 return 0;

        message_vision(HIW "\n$N" HIW "右手" + weapon->name() + HIW "猛然旋转，刀光突"
                       "现，刹那间已将$n" HIW "逼的退无可退。\n" NOR, me, victim);
        addn("neili", -80, me);
        victim->start_busy(2 + random(lvl / 60));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mingyue-blade/" + action;
}