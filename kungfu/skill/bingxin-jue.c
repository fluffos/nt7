//开始阅读文件：/kungfu/skill/bingxin-jue.c
//redl 2014
#include <ansi.h>;
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bingxin-jue", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        if( query("gender", me) == "无性" && query("bingxin-jue", me)>99 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的冰心决。\n");

        if( query("int", me)<31 )
                return notify_fail("你觉得冰心决深奥无比，一时难以领会。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功火候还不够，还不能学习冰心决。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰心决只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bingxin-jue/" + func;
}

int help(object me)
{
        write(HIC"\n冰心决："NOR"\n");
        write(@HELP

    诗仙李白身怀的内功，来历不明。听说他对海外的青梅酒情有独钟。

        学习要求：
                悟性31，非太监
HELP
        );
        return 1;
}
