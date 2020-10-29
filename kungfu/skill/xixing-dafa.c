// xixing-dafa.c 吸星大法

#include <ansi.h>;
inherit FORCE;


int is_pbsk() { return 1; }
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：这种害人的武功，我学它作甚？\n");

/*
        if( !query("family/family_name", me) || query("family/family_name", me) != "日月神教" )
                return notify_fail("你不是日月神教的人，难以修炼吸星大法。\n");
*/

        if( query("con", me)<20 )
                return notify_fail("你试着按照法门运转了一下内息，忽然觉得心火如"
                                   "焚，丹田却是一阵冰凉！\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功修为不足，难以修炼吸星大法。\n");

        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me )
           && lvl < 200
           && lvl >= 10)
                return notify_fail("你没有按照吸星大法的诀窍将内力散去，现在还不"
                                   "敢妄自继续修行大法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("吸星大法只能用学(learn)的来增加熟练度。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int)me->query_skill("xixing-dafa", 1) < 80
           || ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1
            || ob->query_skill_mapped("force") == "taixuan-gong")
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("force");
        if (ap / 2 + random(ap) < dp)
        {
                if( query("neili", me)<query("max_neili", me)*15/10 )
                        addn("neili", jiali, me);

                result = ([ "damage" : -damage ]);

                switch (random(4))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只觉得内力源源而泻"
                                             "，不由得大吃一惊。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只觉得发出的内力犹"
                                             "如石沉大海，不知所踪。\n" NOR ]);
                        break;
                case 2:
                        result += ([ "msg" : HIM "$N" HIM "只觉得发出的内力犹"
                                             "无影无踪，浑然不知着落。\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催动内力，但是"
                                             "只觉得$n竟似毫不费力。\n" NOR ]);
                        break;
                }
                return result;
        }
}
void check_count(object me)
{
        int lvl = me->query_skill("xixing-dafa", 1);

        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me) >= 3000
            && query("exception/xixing-count", me)>1000 )
        {
                // 怪体免疫
                if( !query("special_skill/nopoison", me) &&
                    me->query_skill("yijinjing", 1) < lvl &&
                    me->query_skill("yijin-duangu", 1) < lvl )
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        query("exception/xixing-count", me)/10);
                delete("exception/xixing-count", me);
        }
}

void skill_improved(object me)
{
        addn("exception/xixing-count", me->query_skill("xixing-dafa",1)+1, me);
        check_count(me);
}
string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}

int help(object me)
{
        write(HIC"\n吸星大法："NOR"\n");
        write(@HELP

    日月神教黑木崖的一种内功。

    吸星大法创自北宋年间的逍遥派，分为北冥神功和化功大法两
路，后来从大理段氏和星宿派分别传落，合而为一，称为吸星大法。
主要是继承了化功大法一路，修习者当令丹田常如空箱，恒似深谷，
空箱可贮物，深谷可容水。若有内息，散之于任脉诸穴。
    吸星大法只能拜任我行为师学习，非有相当机缘不能学到。

        学习要求：
                葵花心法
                基本内功10级
                尽量少的正气
                不能学习佛门心法
                散功
HELP
        );
        return 1;
}
