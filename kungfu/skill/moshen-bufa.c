// This program is a part of NITAN MudLIB

inherit SKILL;

string *dodge_msg = ({
        "$n一声长笑，冲天而起，竟能凌空旋，堪堪避过$N的攻击，往另一个方向投去！\n",
        "$N攻向$N时，$n看似要凌空迎战，岂知竟像蝙蝠般旋避开，予人吻合天地大道的感觉。\n",
        "$n身躯后仰，险险避开$N的攻击，再斜飞而起，往远处投去，姿态美至极点。\n",
        "$n好像化成一缕没有重量的轻烟，随呼呼吹来的轻风飘移晃动，每一刻都不断变换位置。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的体力太差了，不能练魔神步法。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}


