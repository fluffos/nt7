// yiwei-dujiang.c 南少林身法一苇渡江

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"HIW"「一苇渡江」"NOR"，前后脚脚尖脚跟相靠，身体如行云流水般滑出丈余。\n",
"$n一式"BLU"「雨燕掠波」"NOR"，双臂前伸，全身贴地平飞，顿时闪过了$N的凌厉攻势。\n",
"$n一式"HIG"「移步换形」"NOR"，足不动，手不抬，一转眼间便绕到了$N的身后。\n",
"$n一式"HIC"「分身化影」"NOR"，一转身间，四面八方飘动着无数个$n的身影，令$N手无足措。\n",
"$n一式"HIY"「孤骛落日」"NOR"，全身笔直，拔地而起，在半空中一转，已落到几丈远的地方。\n",
"$n一式"GRN"「鸿雁双飞」"NOR"，两臂鹏举如翼，在剌剌风声中，从$N头顶横跃而过。\n",
"$n一式"HIY"「苍龙出水」"NOR"，双脚点地，全身化为一道白影，急速绕着$N打了几转。\n",
"$n一式"HIG"「稚凤归巢」"NOR"，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间，动弹不得。\n",
});


int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if( query("dex", me)<25 || query("int", me)<25 )
               return notify_fail("就你这身法还练一苇渡江功？小心弄折了腿。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的体力太差了，无法练习一苇渡江。\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("yiwei-dujiang", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

int difficult_level()
{
        return 300;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yiwei-dujiang", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yiwei-dujiang", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "一招「蜻蜓点水」，脚尖往地一点，身体冲天而起，"
                                            "顿时,$N一招失手！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "$n" HIY "一个「白驹过隙」，身行一侧，提气一纵，"
                                            "$N猛然一招过去，已经收不住去势！\n" NOR]);
                        if (! ob->is_busy())
                                ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "使出「鹞子穿林」，向一旁平平掠出，"
                                            "一个转身折身而下。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一招「蜻蜓点水」，脚尖往地一点，身体冲天而起,"
                                 "可是$N" HIY "早以洞察$n的企图。抢占了先机。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "一个「白驹过隙」，身行一侧，提气一纵，"
                                 "$N拧身而上，全力攻击$n！\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "使出「鹞子穿林」，向一旁平平掠出，"
                                 "$N冷笑几声，身行一拔往高处掠去，凌空搏击$n！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

string perform_action_file(string action)
{
        return __DIR__"yiwei-dujiang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // 过河比普通容易 越高越好
string river_go_msg() {        return HIW"$N捡起一段芦苇抛入水中，紧跟着飞身跃上芦苇，长袖飘飘，渡过了水面。\n"NOR;}
string river_come_msg() {        return HIW"只见$N踩着一段芦苇从对岸过来，姿态潇洒地落在岸边。\n"NOR;}

int help(object me)
{
        write(HIC"\n一苇渡江："NOR"\n");
        write(@HELP

    南少林身法一苇渡江

        学习要求：
           基本内功10级
HELP
        );
        return 1;
}


