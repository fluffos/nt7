// xueying-shenfa

inherit SKILL;

mapping *action = ({
([        "action" : "$n一式「天涯海角」，身轻如燕，从$N身边横跃而过。\n",
        "dodge"  : 110
]),
([        "action" : "$n一式「血海飘香」，如一阵清风，舒缓地闪过了$N的凌厉攻势。\n",
        "dodge"  : 120
]),
([        "action" : "$n一式「血影无踪」，轻盈地一跃，一转眼间便绕到了$N的身后。\n",
        "dodge"  : 130
]),
([        "action" : "$n一式「心血来潮」，一转身间，向后飘出近一丈远\n",
        "dodge"  : 140
]),
([        "action" : "$n一式「血海茫茫」，拔地而起，在半空中一转，已落到几丈远的地方。\n",
        "dodge"  : 150
]),
([        "action" : "$n一式「血刀之影」，淼茫中防似看到红色的刀光。\n",
        "dodge"  : 160
]),
([        "action" : "$n一式「血洗情天」，双脚点地，全身化为一道白影，急速绕着$N打了几转。\n",
        "dodge"  : 170
]),
([        "action" : "$n一式「血魔之影」，漫天红影，围着$N急速地盘旋了几圈。\n",
        "dodge"  : 180
]),
([        "action" : "$n一式「血血血」，漫天红影，围着$N急速地盘旋了几圈。\n",
        "dodge"  : 190
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("xueying-shenfa");

        if (level < 80 )
                zhaoshu--;

        if (level < 60 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        object me, ob;
        mapping action;

        me = this_player();
        action = query_action(me, ob);

        return action["action"];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的体力太差了，不能练血影身法。\n");
        me->receive_damage("qi", 30);
        return 1;
}
