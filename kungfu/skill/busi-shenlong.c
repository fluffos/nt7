// busi-shenlong.c 不死神龙

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        /*
        return force == "shenlong-xinfa" ||
               force == "shedao-neigong";
        */
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("busi-shenlong", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "无性" && 
        (int)me->query_skill("busi-shenlong", 1) > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的不死神龙心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("不死神龙只能通过学或是从运用(exert)中增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"busi-shenlong/" + func;
}

