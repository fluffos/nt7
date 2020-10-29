// buddhism-force.c

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("buddhism-force", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("buddhism-force", 1);

        if( query("gender", me) == "无性" )
                return notify_fail("你无根无性，阴阳不调，难以领会金刚不坏神功。\n");

        if( query("sex/times", me) || query("gender", me) != "男性" )
                return notify_fail("学金刚不坏神功必须是童子之身。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("金刚不坏神功只能用学(learn)的来增加熟练度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"buddhism-force/" + func;
}


void skill_improved(object me)
{
        if( (int)me->query_skill("buddhism-force", 1) == 120 &&
             !query("sl_gift/con", me) )
        {
                addn("con", 1, me);
                set("sl_gift/con", 1, me);
                tell_object(me, HIM "\n你的金刚不坏神功学有所成，提高了你的根骨。\n" NOR);
        }
}
