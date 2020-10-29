// beimin-shengong.c 北冥神功
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_enable(string usage) { return usage=="force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force) { return 1; }

// beiming 内力应该高10倍
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("beiming-shengong", 1);
        return lvl /10 * lvl /10 * 28 * 15 / 10 / 10;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("beiming-shengong", 1);

        if( query("gender", me) == "无性" && lvl>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的北冥神功。\n");

        if( query("con", me)<24 )
                return notify_fail("算了吧，你先天根骨不好，别强学了。\n");

        if( query("int", me)<30 )
                return notify_fail("算了吧，你先天悟性不好，别强学了。\n");

        if (me->query_skill("force", 1) <= lvl)
                return notify_fail("你的基本内功基础不够，再学下去会走火入魔的。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("北冥神功只能用学的，或是从运用(exert)中增加熟练度。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int) me->query_skill("beiming-shengong", 1) < 80 ||
            ob->query_skill_mapped("force") == "taixuan-gong" ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap = ob->query_skill("force") + ob->query_skill("dodge");
        dp = me->query_skill("force") + me->query_skill("dodge");
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只觉得内力源源而泻"
                                             "，不由得大吃一惊。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只觉得发出的内力犹"
                                             "如石沉大海，不知所踪。\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催动内力，但是"
                                             "只觉得$n竟似毫不费力。\n" NOR ]);
                        break;
                }
                return result;
        }
}

/*
// 连招刷内力，导致cpu负担不了，故而取消
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int percent,force1,force2,dodge1,dodge2,lv1,lv2;

        force1 = victim->query_skill("force");
        force2 = me->query_skill("force");
        dodge1 = victim->query_skill("dodge");
        dodge2 = me->query_skill("dodge");

        lv1= force1*dodge1;
        lv2= force2*dodge2;

        lv2 = lv2*3/2;
        if ((int)me->query_skill("beiming-shengong",1)>100
         && !query_temp("weapon", victim )
         && query("max_neili", victim)>500
        && lv1/2 + random(lv2) > lv1 )
        {
                addn("max_neili", -1*(5+(me->query_skill("beiming-shengong",1)/100)), victim);
                if (((int)me->query_current_neili_limit()-me->query_all_buff("max_neili"))*3 >= query("max_neili", me)-me->query_all_buff("max_neili")) 
                addn("max_neili", 1*(5+(me->query_skill("beiming-shengong",1)/100)), me);
                return ([ "msg": HIR "$n只觉息关一开，一股内力被$N吸了过去！\n" NOR ]);
        }

        return damage_bonus;
}
*/

int difficult_level()
{
        return 200;
}

string exert_function_file(string func)
{
        return __DIR__"beiming-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n北冥神功："NOR"\n");
        write(@HELP

    北冥神功为逍遥派无上内功。
    庄子‘逍遥游’有云：‘穷发之北有冥海者，天池也。有鱼焉，
其广数千里，未有知其修也。’又云：‘且夫水之积也不厚，则其
负大舟也无力。覆杯水于坳堂之上，则芥为之舟；置杯焉则胶，水
浅而舟大也。’是故逍遥派武功，以积蓄内力为第一要义。内力既
厚，天下武功无不为我所用，犹之北冥，大舟小舟无不载，大鱼小
鱼无不容。是故内力为本，招数为末。北冥神功系引世人之内力而
为我有。北冥大水，非由自生。语云：百川汇海，大海之水以容百
川而得。汪洋巨浸，端在积聚。
    世人练功，皆自云门而至少商，我逍遥派则反其道而行之，自
少商而至云门，拇指与人相接，彼之内力即入我身，贮于云门等诸
穴。然敌之内力若胜于我，则海水倒灌而入江河，凶险莫甚。逍遥
派旁支，未窥要道，惟能消敌内力，不能引而为我用，犹日取千金
而复弃之于地，暴殄珍物，殊可哂也。

        学习要求：
                基本内功10级
                太监无法学到50级以上的北冥神功
HELP
        );
        return 1;
}
