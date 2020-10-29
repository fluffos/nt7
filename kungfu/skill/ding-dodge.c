// ding-dodge.c 丁字步 

inherit SKILL;
int is_pbsk() { return 1; }

string *dodge_msg = ({
        "$n漫不经心的向左迈出一步，刚好避过$N的凌厉攻势。\n",
        "可是$n恰巧往右走了一步，躲过了$N这一招。\n",
});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的体力太差了，迈不开丁字步。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

