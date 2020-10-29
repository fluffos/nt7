// baihong-jianfa 白虹剑法

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *action_msg = ({
        "$N左手握拳，右手剑走轻灵，一招巧「白虹一现」，$w化成一道光芒，射向$n的$l",
        "$N使出一招「鹰起云扬」，身形向上飘起，手中$w猛的劈向$n的$l",
        "$N身形一晃，猛然一式「波涛汹涌」，将$w舞得有如波涛，挟着一阵劲风向$n扫去",
        "$N一身清嘯，身行一顿，随即将手中$w舞成一道光环，一招「日月无光」卷起地上的灰尘扫$n的$l",
        "$N倒转身子，似乎象要逃跑，猛然身行一转，使出一招“回手剑”，剑尖化作几点星光射向$n的$l",
        "$N向左跨出一步，左手捏着剑决，一招「百流汇海」右手$w化出好几道光芒射向$n的$l",
        "$N运力纵起丈余，一招「天鹰翱翔」，挥出手中$w，飘然刺向$n的$l",
        "$N右手举$w过顶，身子一摆，一招「冰霜雪雨」，$w化做几点寒星射向$n",
        "$N将左手握拳，虚击一招，突然面如寒霜，挥出手中$w刺向$n的$l，好一招「风雪江山」",
        "$N手中$w一指，脸上露出微微的笑容，真气飞速地流遍全身，一招「白虹万道」，$w化成万道光芒雷霆般射向$n的$l",
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(21),
                "attack": 20 + random(11),
                "dodge" : -30 + random(11),
                "parry" : -30 + random(11),
                "damage_type" : random(2)?"刺伤":"割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练白虹剑法。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练白虹剑法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baihong-jianfa/" + action;
}

