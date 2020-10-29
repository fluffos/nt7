// shaolin-shenfa.c 少林身法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }
int is_pbsk() { return 1; }

string *dodge_msg = ({
        "$n一式"HIW"「一苇渡江」"NOR"，前后脚脚尖脚跟相靠，身体如行云流水般滑出丈余。\n",
        "$n一式"BLU"「雨燕掠波」"NOR"，双臂前伸，全身贴地平飞，顿时闪过了$N的凌厉攻势。\n",
        "$n一式"HIC"「移步换形」"NOR"，足不动，手不抬，一转眼间便绕到了$N的身后。\n",
        "$n一式"HIG"「分身化影」"NOR"，一转身间，四面八方飘动着无数个$n的身影，令$N手无足措。\n",
        "$n一式"HIY"「孤骛落日」"NOR"，全身笔直，拔地而起，在半空中一转，已落到几丈远的地方。\n",
        "$n一式"HIB"「鸿雁双飞」"NOR"，两臂鹏举如翼，在剌剌风声中，从$N头顶横跃而过。\n",
        "$n一式"HIY"「苍龙出水」"NOR"，双脚点地，全身化为一道白影，急速绕着$N打了几转。\n",
        "$n一式"GRN"「稚凤归巢」"NOR"，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间，动弹不得。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的体力太差了，无法能练习少林身法。\n");

        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // 过河比普通容易 越高越好
string river_go_msg() {        return HIW"$N捡起一段芦苇抛入水中，紧跟着飞身跃上芦苇，长袖飘飘，渡过了水面。\n"NOR;}
string river_come_msg() {        return HIW"只见$N踩着一段芦苇从对岸过来，姿态潇洒地落在岸边。\n"NOR;}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shaolin-shenfa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shailin-shengfa", 1);

        // 一个经典的算法
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                // 去掉所有的伤害写法

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一式「稚凤归巢」，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间，动弹不得。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(3));
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "一式「一苇渡江」，前后脚脚尖脚跟相靠，身体如行云流水般滑出丈余。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(1));
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "一式「分身化影」，一转身间，四面八方飘动着无数个$n的身影，令$N手无足措。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

string perform_action_file(string action)
{
        return __DIR__"shaolin-shenfa/" + action;
}

int help(object me)
{
        write(HIC"\n少林身法："NOR"\n");
        write(@HELP

    少林身法为少林本门轻功身法。少林轻功名冠天下。

        学习要求：
                混元一气功10级
HELP
        );
        return 1;
}

