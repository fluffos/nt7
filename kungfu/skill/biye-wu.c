// This program is a part of NITAN MudLIB
// biye-wu.c 碧叶随风舞

inherit SKILL;

string *action_msg = ({
        "$N双手扬起，轻飘飘一式「叶落」，掌若落叶，向$n的$l拍去",
        "$N左脚为轴心，右脚一旋，双手交替挥舞，如竹叶翻飞，正是「叶舞」，向$n的$l拍下",
        "$N身体高高跃起，左手立在胸前，右臂微曲，使一招「叶飘零」，向$n的$l和面门打去",
        "$N微一运劲，双掌青筋爆露，一式「枯叶」，将$n浑身上下都笼罩在重重掌影之中",
        "$N双掌平摊，左掌缓缓收至肩，右掌猛向前推出，\n掌风带着破空声，一招「弹枝」，如竹枝反弹，直奔$n心窝而去",
        "$N突然收掌，由腹部向前向上推出，掌风如涛，一式「叶如潮」，一片劲风直逼$n",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练碧叶随风舞必须空手。\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 30)
                return notify_fail("你的碧云心法火候不够，无法学碧叶随风舞。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练碧叶随风舞。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(100),
                "dodge" : -40 + random(10),
                "parry" : -50 + random(10),
                "attack": 10 + random(20),
                "damage_type":random(2)?"搓伤":"淤伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练碧叶随风舞。\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"biye-wu/" + action;
}
