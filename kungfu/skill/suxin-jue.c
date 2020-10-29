inherit FORCE;

int valid_enable(string usage) 
{ 
        return usage == "force"; 
}

int valid_force(string force)
{
        return 1;
        return force == "yunv-xinfa" ||
               force == "quanzhen-xinfa";
}

int valid_learn(object me)
{
            return 1;
}

int practice_skill(object me)
{
        return notify_fail("素心决只能用学(learn)来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"suxin-jue/" + func;
}
