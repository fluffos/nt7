// chanchu_bufa.c 蟾蜍步法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只见$n一招"HIY"「蟾飞九天」"NOR"，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
        "但是$n一个使出"HIY"「蛙鸣震天」"NOR"，身形飘忽，轻轻一纵，早已避开。\n",
         "$n一招"HIY"「蛙入稻田」"NOR"，身行随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n一个"HIY"「蟾蜍扑虫」"NOR"，侧身一让，$N这一招扑了个空。\n",
        "却见$n"HIY"「蟾翻白肚」"NOR"，足不点地，往旁窜开数尺，躲了开去。\n",
        "$n身形一招"HIY"「金蟾归月」"NOR"，身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的体力太差了，不能练蟾蜍步法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);

        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("chanchu-bufa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("chanchu-bufa", 1) / 2;

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : WHT "$n" WHT "身体向下一伏，手脚飞快地搅动起地上的尘土，匪所思疑地往后一纵，\n"
                                            "$N只见眼前弥漫着一阵呛人尘烟，视线一片模糊！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : WHT "$n" WHT "身体向后一翻，向后纵出数丈之远，"
                                            "$N情急之下，额头的汗都出来了！\n" NOR]); ;

                        break;
                default:
                        result += (["msg" : WHT "$n" WHT "一个侧身闪过，"
                                            "竟然不留一丝痕迹。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = WHT "$n" WHT "身体向下一伏，手脚飞快地搅动起地上的尘土，匪所思疑地往后一纵，\n"
                                 "$N" WHT "猛地向前一冲，早突过尘烟，来到$n的身后。\n" NOR;
                        break;
                case 1:
                        result = WHT "$n" WHT "身体向后一翻，向后纵出数丈之远，\n"
                                 "$N一个箭步就冲到了$n面前！\n" NOR;
                        break;
                default:
                        result = WHT "$n" WHT "一个侧身闪过，"
                                 "$N就象影子一样紧紧地咬住！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;
        lvl = me->query_skill("chanchu-bufa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 40;
        if (lvl < 280) return 70;
        if (lvl < 350) return 90;
        return 110;
}


int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point() { return 1.1; }

int help(object me)
{
        write(HIC"\n蟾蜍步法："NOR"\n");
        write(@HELP

    白驼山本门轻功。

        学习要求：
           蛤蟆功10级
HELP
        );
        return 1;
}
