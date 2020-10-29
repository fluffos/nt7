// riyue-guanghua.c 日月光华
// By haiyan

#include <combat.h> 
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "riyue-xinfa" || force == "pixie-jian";
}

int query_neili_improve(object me)
{
    int lvl;
    lvl = (int)me->query_skill("riyue-guanghua", 1);
    return lvl * lvl * 22 * 15 / 100 / 200;
}

int valid_learn(object me)
{
    if( !query("special_skill/ghost", me)){
    if( query("gender", me) == "男性" && 
         (int)me->query_skill("riyue-guanghua", 1) > 49 )
            return notify_fail("你六根未净，难以领会更高深的「日月光华」。\n");

    if( query("gender", me) == "女性" )
            return notify_fail("你无法领会「日月光华」这门绝学。\n");
        }

    if( query("character", me) == "光明磊落" )
            return notify_fail("你心中暗想：我为人光明磊落，这种邪教功夫学来做甚。\n");

/*
    if ( (int)me->query_skill("xixing-dafa", 1) > 0 )
            return notify_fail("你已学了吸星大法，不能修炼日月光华。\n");
*/

    if( query("dex", me)<25 )
            return notify_fail("你的身手不够灵活，无法领会日月光华的秘要。\n");

    if ((int)me->query_skill("riyue-xinfa", 1) < 100)
            return notify_fail("你的日月心法火候还不够，难以领会日月光华。\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("riyue-guanghua", 1))
            return notify_fail("你的基本内功水平有限，不能领会更高深的日月光华。\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("日月光华只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
/*
    mapping sk;
    string *skname;
    int i, k=0;

    if (mapp(query("reborn", this_player())))
        return __DIR__"riyue-guanghua/" + func;

    sk=this_player()->query_skills();
    skname=sort_array( keys(sk), (: strcmp :) );

    for(i=0; i < sizeof(sk); i++)
    {
        if (SKILL_D(skname[i])->valid_enable("force"))  k++;
    }

    if ( k >=10 )
    {
        tell_object(this_player(), "你体内不同内力互相冲撞，难以施展日月光华。\n");
        return 0;
    }
*/

    return __DIR__"riyue-guanghua/" + func;
}
