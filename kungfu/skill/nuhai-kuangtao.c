// nuhai-kuangtao.c    怒海狂涛

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "yunv-xinfa" ||
               force == "jiuyang-shengong";
}


int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nuhai-kuangtao", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "无性" )
                return notify_fail("你无根无性，阴阳难调，不能修习怒海狂涛。\n");

        if( query("gender", me) == "女性" )
                return notify_fail("怒海狂涛是刚猛内功，不适宜女孩子学。\n");


        if ((int)me->query_skill("yunv-xinfa", 1) < 50)
                return notify_fail("你的玉女心法火候还不够。\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的基本剑法火候还不够。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的基本内功火候还不够。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("怒海狂涛只能用学(learn)来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"nuhai-kuangtao/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short" : me->name()+"盘膝坐在地上，四周隐隐有风声海啸，气息激荡。",
"start_self"  : HIG"你盘膝而坐，内力源源不断的流转全身，开始运功疗伤。\n"NOR,
"on_self"     : HIM"你耳边隐隐风雷阵阵，碧海狂啸，体内真气彭湃，伤势渐渐好转。\n"NOR,
"start_other" : HIG""+me->name()+"盘膝坐下，片刻间，隐隐传来风声海啸，空气里真力激荡。\n"NOR,
"finish_self" : HIG"你感到海啸声渐渐消退，内力充沛，伤势已然痊愈，站起身来。\n"NOR,
"finish_other" :me->name()+"一声长啸，如同滔天海浪席卷而来，待其挺身而立，却是精神饱满。\n",
"unfinish_self" :"你感到内力断断续续，无法继续疗伤，如此下去，势必走火入魔，只得暂缓疗伤。\n",
"unfinish_other":me->name()+"摇晃起身，脸上一阵抽搐，好象伤势十分严重。\n",
"halt_self"   : "你深吸一口气，摒除耳边波浪啸声，压下真气，站起身来。\n",
"halt_other"  : me->name() +"深吸口气，站起身来，伤势似乎有所好转。\n",
        ]);
}
