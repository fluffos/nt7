// Code of ShenZhou
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

inherit POISON;

string name() { return "huadu_poison"; }

string chinese_name() { return "星宿虫毒"; }
string *query_valid_force() 
{ 
        return ({
                "yijinjing",
                "lengyue-shengong",
                "bahuang-gong",
                "beiming-shengong",
                });
}


string update_msg_others()
{
        return HIM "$N" HIB "的目光散乱，神色异常，脸上泛出一层黑气。\n" NOR;
}

string update_msg_self()
{
        return HIR "你忽然肺腑一阵剧痛，你体内的星宿虫毒发作了，你觉的这次毒力来的更凶猛！\n" NOR;
}