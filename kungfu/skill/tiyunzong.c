// tiyunzong.c 梯云纵

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只见$n一招"HIW"「白鹤冲天」"NOR"，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
        "$n一个"BLU"「鹞子翻身」"NOR"，向后纵出数丈之远，避开了$N的凌厉攻势。\n",
        "$n使出"HIY"「大鹏展翅」"NOR"，向一旁飘然纵出，轻轻着地。\n",
        "但是$n一招"HIC"「白鹤冲天」"NOR"身形飘忽，轻轻一纵，早已避开。\n",
        "$n身随意转，一招"HIB"「鹞子翻身」"NOR"倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n一招"YEL"「大鹏展翅」"NOR"侧身一让，$N这一招扑了个空。\n",
        "却见$n足不点地一招"HIC"「白鹤冲天」"NOR"，往旁窜开数尺，躲了开去。\n",
        "$n身形微晃，一招"MAG"「鹞子翻身」"NOR"有惊无险地避开了$N这一招。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你基本轻功修为有限，难以修炼梯云纵。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你内力修为太浅，难以修炼梯云纵。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 || query("neili", me)<10 )
                return notify_fail("你的体力太差了，无法练习梯云纵。\n");
        me->receive_damage("qi", 50);
        addn("neili", -10, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("tiyunzong", 1);

        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tiyunzong", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
           ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge") +
             me->query_skill("tiyunzong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一招「白鹤冲天」，身体向上笔直地纵起丈余，"
                                            "$N顿然失去目标，劲招失手！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "一个「鹞子翻身」，向后纵出数丈之远，"
                                            "$N一招失手，攻守之势已露破绽！\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "使出「大鹏展翅」，向一旁飘然纵出，"
                                            "已然毫发无损地轻轻着地。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一招「白鹤冲天」，身体向上笔直地纵起丈余，"
                                 "可是$N" HIY "早以看破$n的企图。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "一个「鹞子翻身」，向后纵出数丈之远，"
                                 "$N立刻跟上随手挥招直入，进袭$n！\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "使出「大鹏展翅」，向一旁飘然纵出，"
                                 "突然发现$N速度更快，也先等候在此！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}


string perform_action_file(string action)
{
      return __DIR__"tiyunzong/" + action;
}

int help(object me)
{
        write(HIC"\n梯云纵："NOR"\n");
        write(@HELP

    梯云纵为武当最高轻功心法。

        学习要求：
          太极神功10级
HELP
        );
        return 1;
}
