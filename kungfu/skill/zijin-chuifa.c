// zijin-chuifa.c 紫金锤法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N双手一震，手中$w夹带着闷雷般的响声，劈头盖脸地就向$n砸了过去。",
        "force"  : 100,
        "dodge"  : -3,
        "parry"  : 15,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type": "挫伤"
]),
([      "action" : "只见$N眼冒凶光，青筋凸起，抄起$w就朝$n的$l狠命扫去。",
        "force"  : 150,
        "dodge"  : -5,
        "parry"  : 20,
        "damage" : 30,
        "lvl"    : 20,
        "damage_type": "瘀伤"
]),
([      "action" : "$N手中的$w举重若轻，势若疯虎地向$n$l连连砸去。",
        "force"  : 180,
        "dodge"  : -8,
        "parry"  : 20,
        "damage" : 40,
        "lvl"    : 50,
        "damage_type": "瘀伤"
]),
([      "action" : "$N全然不顾$n的招式，举起$w朝着$n当头就是一锤。",
        "force"  : 210,
        "dodge"  : -12,
        "parry"  : 30,
        "damage" : 50,
        "lvl"    : 80,
        "damage_type": "挫伤"
]),
([      "action" : "$N将$w高举过肩，蓄紧力发，对准$n的$l发出雷霆一击。",
        "force"  : 250,
        "dodge"  : -15,
        "parry"  : 35,
        "damage" : 60,
        "lvl"    : 100,
        "damage_type": "瘀伤"
]),
});

int valid_learn(object me)
{
    object ob;

    if( (int)me->query_skill("force", 1) < 30)
        return notify_fail("你的内功火候还不够。\n");

    if( (int)me->query_skill("hammer", 1) < 50)
        return notify_fail("你的基本锤法水平太低。\n");

    if( query("max_neili", me)<250 )
        return notify_fail("你的内力不够，不能练紫金锤法。\n");

    if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("zijin-chuifa", 1))
        return notify_fail("你的基本锤法水平有限，无法领会更高深的紫金锤法。\n");

    if( !objectp(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "hammer" )
            return notify_fail("你使用的武器不对，无法练习紫金锤法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="hammer" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int)me->query_skill("zijin-chuifa", 1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object ob;

    if( query("qi", me)<50 )
        return notify_fail("你的体力太低，没有办法练习紫金锤法。\n");

    if( query("neili", me)<50 )
        return notify_fail("你的内力不够，没有办法练习紫金锤法。\n");

    if( !objectp(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "hammer" )
            return notify_fail("你使用的武器不对，无法练习紫金锤法。\n");

    me->receive_damage("qi", 45);
    addn("neili", -41, me);
    return 1;
}
