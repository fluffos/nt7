// piaoyi-bu.c

inherit SHAOLIN_SKILL;

string *dodge_msg = 
        ({
        "$n一个「银鹭渡海」，跃起数尺，躲过了$N这一招。\n",
        "$n身形向后一纵，使出一招「玉兔落尘」，避过了$N的攻击。\n",
        "$n使出「锦鲤穿沙」，恰好躲过了$N的攻势。\n",
        "$n一招「灵狐幻遁」，姿态美妙地躲了开去。\n"
        "$n使出一招「巧燕穿云」，猛然纵起丈余，结果$N扑了个空。\n",
        "$n身形一摇，幻出几个人影，一招「望穿秋水」躲过了$N的攻势。\n",
        "$n左一摇，右一晃，一招「紫燕呢喃」已轻松闪过。\n",
        "$n一招「飞鸟投林」纵身跃起，倏忽已落至$N身后。\n",
        });

int valid_enable(string usage)
{
        return (usage == "dodge");
}


int valid_learn(object me)
{

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法学飘逸步。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力太弱，无法练飘逸步。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("piaoyi-bu", 1))
                return notify_fail("你基本轻功火候不够，无法领会更高深的飘逸步。\n");
        
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你基本轻功火候不够，无法领会高深的飘逸步。\n");

        return 1;
}


string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{       
        int ci;
        if( query("qi", me)<100 )
                return notify_fail("你的体力太差了，不能练飘逸步法。\n");
        if (me->query_skill("piaoyi-bu", 1) < 100)
                me->receive_damage("qi", 30);
        else if (me->query_skill("piaoyi-bu", 1) > 100)
        {    
             if( query("neili", me)<170 )
                     return notify_fail("你的内力不够练飘逸步法。\n");

                me->receive_damage("qi", ci);
        }
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"piaoyi-bu/" + action;
}
