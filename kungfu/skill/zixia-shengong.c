// zixia-shengong.c 紫霞神功

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("zixia-shengong", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, t, level;

        level = (int)me->query_skill("zixia-shengong", 1);

        if (level <= 100)
                for (i = 1; i < level / 10; i++)
                        t *= 2;

        if( query("gender", me) == "无性" && level>49 )
                return notify_fail("公公无根无性，紫霞神功再难更上一层楼。\n");

        if ((int)me->query_skill("zixia-shengong", 1) >= 45
        &&  (int)me->query_skill("huagong-dafa", 1) >= 100
        &&  (int)me->query_int() < 100 )
                return notify_fail("你受高深的邪派内功牵绊，与紫霞神功水火难容，以你的智商再难更上一层楼。\n");

        if (level <= 100)
        {
                if( level>10 && query("shen", me)<t*100 )
                        return notify_fail("你的侠义正气太低了，无法领会更高深的紫霞神功。\n");
        }
        else if( level < 1000 )
        {
                if( query("shen", me)<(51200+(level-100)*1000) )
                        return notify_fail("你的侠义正气太低了，无法领会更高深的紫霞神功。\n");
        }
        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("紫霞神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
int help(object me)
{
        write(HIM"\n紫霞神功："NOR"\n");
        write(@HELP

    华山气宗内功，具自疗及运功之用，并能增加精气。精的增加
视乎于自身紫氤吟的修为，气的增加则决定于自身正气诀的修为。

        学习要求：
                基本内功10级
                相应的正气
                太监无法学到50级以上的紫霞神功
HELP
        );
        return 1;
}
