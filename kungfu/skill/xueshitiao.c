// xueshitiao.c 雪狮跳

inherit SKILL;

string *dodge_msg = ({
        "$n一式「冰消雪融」，一下滑到丈外开去，把$N攻势化於无形。\n",
        "$n使出「金狮狂舞」，一个筋斗从$N头上一翻而过，$N打$n不着。\n",
        "$n脚步虚踩，忽左而右，使出「雪入黄河」从$N的腋下穿到$P身後。\n",
        "$n微笑中後退两步，身子一顿，一式「飞雪藏形」躲过$N这一击。\n",
        "$n掉转身子，轻轻一跃，一式「狮子摇头」轻描淡写地化开$N这一招。\n",
        "$n身子向上一纵，使出一式「踏雪无痕」跃起数尺，飘然落到一旁。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的体力太差了，不能练雪狮跳。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
        return 1;
}

