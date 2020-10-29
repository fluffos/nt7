// yinyun-ziqi.c 氤氲紫气
// 武当初级内功
// Created by Lonely

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyun-ziqi", 1);
        return lvl * lvl * 15 * 19 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yinyun-ziqi", 1);
        int t = 1, j;

        for (j = 1; j < lvl / 10; j++) 
                t *= 2;
        if (t > 5000) t = 5000;
        if( query("gender", me) == "无性" && lvl>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的氤氲紫气神功。\n");

        if( query("class", me) == "bonze" )
                return notify_fail("氤氲紫气讲究阴阳调合，有违佛家六根清净之意，"
                                +RANK_D->query_respect(me)+"欲修此功，已是罪过。\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的基本内功火候还不够。\n");

        if( (lvl>10 && lvl<100 && query("shen", me)<t*200 )
                 || (lvl >= 100 && query("shen", me)<10000) )
                return notify_fail("你的侠义正气太低了。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("氤氲紫气只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "status_msg" : "头顶氤气蒸蒸，神色威严",
                "start_my_msg" : "盘膝而坐，双目紧闭，深深吸一口气引如丹田，慢慢让一股内息在周身大穴流动，渐入忘我之境。\n",
                "start_other_msg" : "盘膝坐了下来，双手虚握成拳，不一会，头顶冒出氤氤紫气。\n",
                "halt_msg" : "微一簇眉，将内息压回丹田，长出一口气，站了起来。\n",
                "end_my_msg" : "将内息在体内运行十二周天，返回丹田，只觉得全身暖洋洋的。\n",
                "end_other_msg" : "长出一口气，一抖衣襟，站了起来，眼中精光一闪。\n"
        ]);
}

