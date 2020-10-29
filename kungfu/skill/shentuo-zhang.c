// This program is a part of NITAN MudLIB
// shentuo-zhang 神驼雪山掌

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N双臂一舒，使出一招「明驼西来」，身形旋转，掌势飘忽，击向$n的$l",
        "$N身形向后一错，左掌阴势，右掌阳型，使出一式「大漠冰扬」，拍向$n的$l",
        "$N弹腿飞身，步法阴阳互易，若有若无的踢向$n的$l，正是一招「灵驼骏足」",
        "$N身形飞旋，一式「万里飞霜」，掌影纷飞，掌上内劲已把$n的上盘统统罩住",
        "$N身形急转，半空中一招「神驼冲霄」，头下脚上，刹那间手脚齐攻，击向$n的$l",
        "$N掌势一缓，使出一式「雪锁千山」，掌上阴劲如怒涛汹涌，缓缓推向$n的$l",
});


int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

// int valid_combine(string combo) { return combo == "lingshe-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练神驼雪山掌必须空手。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练神驼雪山掌。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force": 320 + random(60),
                "attack": 50 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"瘀伤":"内伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练神驼雪山掌。\n");
        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shentuo-zhang/" + action;
}