// ding-force.c 小丁气功

inherit FORCE;
int is_pbsk() { return 1; }

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("ding-force", 1);
        return lvl * lvl * 19 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("gender", me) == "无性" && me->query_skill("ding-force",1)>49 )
                return notify_fail("公公无根无性，小丁气功再难更上一层楼。\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("小丁气功只能跟小丁学来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"ding-force/" + func;
}


