#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("longxiang-gong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
        /*
        return force == "mizong-neigong" ||
               force == "xiaowuxiang" ||
               force == "yijinjing" ||
               force == "xixing-dafa";
        */
}

mapping *action = ({
([      "action" : "$N单掌一抖，运聚龙象般若功功力，呼啸着向$n的$l处拍去",
        "dodge"  : 37,
        "force"  : 430,
        "attack" : 173,
        "parry"  : 41,
        "damage" : 133,
        "damage_type": "内伤"
]),
([      "action" : "$N右拳横移，左掌运起龙象般若功的劲力，猛地拍向$n的$l",
        "dodge"  : 35,
        "force"  : 440,
        "attack" : 177,
        "parry"  : 47,
        "damage" : 121,
        "damage_type": "内伤"
]),
([      "action" : "$N吐气扬声，双拳同时运满龙象般若功功力，朝$n$l处贯去",
        "dodge"  : 37,
        "force"  : 450,
        "attack" : 182,
        "parry"  : 46,
        "damage" : 123,
        "damage_type": "内伤"
]),
([      "action" : "$N运足龙象般若功，双拳平推，顿时一股凌厉的罡劲直袭$n",
        "dodge"  : 27,
        "force"  : 480,
        "attack" : 183,
        "parry"  : 35,
        "damage" : 145,
        "damage_type": "内伤"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("longxiang-gong", 1);

        if (lvl >= 150)
                return usage == "force" ||
                       usage == "parry" ||
                       usage == "unarmed";

        else if (lvl >= 30)
                return usage == "force";

        else
                return usage == "force";
}

int valid_learn(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if( query("str", me)<30 )
                return notify_fail("你的先天膂力孱弱，无法修炼龙象般若功。\n");

        if( query("con", me)<30 )
                return notify_fail("你的先天根骨孱弱，无法修炼龙象般若功。\n");

        if( query("gender", me) == "无性" && layer >= 1 )
                return notify_fail("你无根无性，阴阳不调，无法修炼龙象般若功。\n");

        if ((int)me->query_skill("lamaism", 1) < 100)
                return notify_fail("你对密宗心法理解不够，难以领会龙象般若功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不足，难以领会龙象般若功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，难以领会龙象般若功。\n");

        if (me->query_skill("force", 1) < lvl)
                return notify_fail("你的基本内功水平不够，难以修炼更深厚的龙象般若功。\n");

        if( query("max_neili", me)<layer*500 )
                return notify_fail("你的内力修为不够，难以修炼更深厚的龙象般若功。\n");

        if (me->query_skill("lamaism", 1) < layer * 25)
                return notify_fail("你对密宗心法理解不够，难以修炼更深厚的龙象般若功。\n");

        if (me->query_skill("unarmed", 1) < lvl && layer >= 5)
                return notify_fail("你的基本拳脚水平不够，难以修炼更深厚的龙象般若功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if (damage_bonus < 130
           || layer < 6
            || query("neili", me)<500
            || query_temp("weapon", me )
            || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "longxiang-gong"
           || me->query_skill_mapped("unarmed") != "longxiang-gong"
           || me->query_skill_prepared("unarmed") != "longxiang-gong"
           || damage_bonus / 6 < victim->query_con() / 10
           //|| random(10) < 5
           )
                return 0;

        if (layer >= 10 && random(2) == 1)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 50) / 3, me);
                return HIY "$N" HIY "拳锋之上竟蕴藏着『" HIR "十龙十象"
                       HIY "』之力，罡劲破体，摧毁了$n" HIY "的真元！\n" NOR;
        } else
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                return HIY "$N" HIY "双拳暗含龙象般若功第" + chinese_number(layer) +
                       "层功力，$n" HIY "心脉受震，喷出一口鲜血！\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("龙象般若功只能用学(learn)来增加熟练度。\n");
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if( lvl>400 && !query("can_perform/longxiang-gong/zhen", me) )
        {
                tell_object(me, HIR "你突然灵犀一动，领悟出数百年无人练成的真·般若极秘诀！\n" NOR);
                set("can_perform/longxiang-gong/zhen", 1, me);
        }

        if ((lvl % 30) == 0 && layer > 13)
        {
                tell_object(me, HIY "你的龙象般若功又进了一层。\n" NOR);
        } else
        if ((lvl % 30) == 0)
        {
                tell_object(me, HIY "你炼成了第" + chinese_number(layer) +
                                "层的龙象般若功。\n" NOR);
        }
}

int difficult_level()
{
        object me;
        int lvl;

        if (me = this_player())
        {
                // 有小无相功？难以学习。
                if (lvl = me->query_skill("xiaowuxiang", 1))
                        return 3000;

                // 有九阳神功？较难学习。
                if (lvl = me->query_skill("jiuyang-shengong", 1))
                        return 1000;
        }

        return 300;
}
string perform_action_file(string action)
{
        return __DIR__"longxiang-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"longxiang-gong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n龙象般若功："NOR"\n");
        write(@HELP

    “龙象般若功”，那是密宗中至高无上的护法神功。为雪山派
本门内功。【龙象般若经】言道，功成十层以上，每出一招，均具
十龙十象的大力，故名“龙象般若功”。

    “龙象般若功”共分十三层，第一层功夫十分浅易，纵是下愚
之人，只要得到传授，一二年中即能练成。第二层比第一层加深一
倍，需时三四年。第三层又比第二层加深一倍，需时七八年。如此
成倍递增，越是往后，越难进展。待到第五层以后，欲再练深一层，
往往便须三十年以上苦功。密宗一门，高僧奇士历代辈出，但这一
十三层“龙象般若功”却从未有一人练到十层以上。这功夫循序渐
进，本来绝无不能练成之理，若有人得享千岁高龄，最终必臻第十
三层境界，只是人寿有限，密宗中的高僧修士欲在天年终了之前练
到第七层、第八层，便非得躁进不可，这一来，往往陷入了欲速不
达的大危境。北宋年间，藏边曾有一位高僧练到了第九层，继续勇
猛精进，待练到第十层时，心魔骤起，无法自制，终于狂舞七日七
夜，自终绝脉而死。

        学习要求：
                基本内功10级
                相应的戾气
                非出家喇嘛不能学到30级以上的龙象般若功
                太监不能学到50级以上的龙象般若功
HELP
        );
        return 1;
}
