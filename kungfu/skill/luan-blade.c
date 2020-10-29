// This program is a part of NITAN MudLIB
// Luan-blade.c 乱刀（田伯光）

inherit SKILL;

string *action_msg = ({
        "$N手中$w左一挥右一拦，对准$n的$l就是一戳",
        "$N手中$w上一挑下一撩，向$n的$l捅去",
        "$N手中$w东一劈西一插，刀锋指向$n的$l",
        "$N手中$w前一指后一扫，刀尖挑向$n的$l",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(41),
                "attack": 60 + random(21),
                "dodge" : -60 + random(21),
                "parry" : -60 + random(21),
                "damage_type" : random(2) ? "挫伤" : "割伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练乱刀。\n");
        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luan-blade/" + action;
}