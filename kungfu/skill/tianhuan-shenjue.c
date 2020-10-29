inherit FORCE;
int is_pbsk() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "riyue-xinfa" ||
               force == "xixing-dafa" ||
               force == "yijinjing" ||
               force == "kuihua-mogong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("tianhuan-shenjue", 1);
        return lvl * lvl * 15 * 8 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("tianhuan-shenjue", 1);

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的基本内功火候还不够。\n");

        // 因为是日月神教的内功，所以对无性的学习限制放宽
        if( query("gender", me) == "无性" && lvl>99 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的天寰神诀。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("天寰神诀只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"tianhuan-shenjue/" + func;
}
