inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候还不够，还不能学习圣火心法。\n");

        return ::valid_learn(me);
}

int valid_force(string force)
{
        // return (force == "shenghuo-shengong");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("圣火心法只能用学(learn)的来增加熟练度。\n");
}


string exert_function_file(string func)
{
        return __DIR__"shenghuo-xinfa/" + func;
}