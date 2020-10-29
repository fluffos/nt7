// 罗汉伏魔神功 luohan-fumogong.c
// Editd By Vin On 29/5/2002

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return 1;
}

int is_pbsk() { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        string fam;

        fam=query("family/family_name", me);
        lvl = (int)me->query_skill("luohan-fumogong", 1);

        // 喝过玄冰碧火酒并且门派为少林
        if( query("skybook/item/xuanbingjiu", me )
           && fam == "少林派"
            && query("class", me) == "bonze" )
                return lvl * lvl * 15 * 18 / 100 / 200;
        else

        // 没喝过玄冰碧火酒但门派为少林
        if( query("class", me) == "bonze"
           && fam == "少林派")
                return lvl * lvl * 15 * 15 / 100 / 200;
        else

        // 喝过玄冰碧火的其他门派玩家
        if( query("skybook/item/xuanbingjiu", me) )
                return lvl * lvl * 15 * 12 / 100 / 200;
        else
        // 普通情况
                return lvl * lvl * 15 * 4 / 100 / 200;
}

int valid_enable(string usage)
{ 
        return usage == "force";       
}

int valid_learn(object me)
{
        if( query("character", me) == "心狠手辣" )
                return notify_fail("你心中暗道：此功一点气势也无，何苦费力学它。。\n");

        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你心中暗道：此功平淡无奇，何苦为它花费心思。\n");

        if( query("int", me)<30 )
                return notify_fail("你先天悟性不足，难以领会罗汉伏魔神功。\n");

        if( query("con", me)<30 )
                return notify_fail("你先天根骨孱弱，无法修炼罗汉伏魔神功。\n");

        if( query("gender", me) == "无性" && query("luohan-fumogong", me)>29 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的罗汉伏魔神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不足，不能学罗汉伏魔神功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，不能学罗汉伏魔神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("罗汉伏魔神功只能用学(learn)的来增加熟练度。\n");
}

int difficult_level(object me)
{
        string fam;
    
        me = this_player();

        fam=query("family/family_name", me);

        if( query("skybook/item/xuanbingjiu", me )
           && fam == "少林派"
            && query("class", me) == "bonze" )
                return 200;
        else

        if( query("class", me) == "bonze"
           && fam == "少林派")
                return 400;
        else

        if( query("skybook/item/xuanbingjiu", me) )
                return 600;
        else
                return 800;
}

string exert_function_file(string action)
{
        return __DIR__"luohan-fumogong/" + action;
}
