// huashan-neigong.c 华山心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int level = (int)me->query_skill("huashan-neigong", 1);
        if( query("gender", me) == "无性" && level>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的华山内功。\n");
        return ::valid_learn(me);
}

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("huashan-neigong", 1);
        return lvl * lvl * 18 * 15 / 100 / 200;
}

int practice_skill(object me)
{
        return notify_fail("华山心法只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huashan-neigong/" + func;
}

