#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiantian-gong", 1);
        lvl += me->query("yuanshen_level") * lvl / 100;
        return (lvl / 10) * (lvl / 20) * 15 * 22 / 100;
}

int valid_force(string force)
{
        return 1;
        return force == "quanzhen-xinfa" ||
               force == "xuanmen-neigong";
}

mapping *action = ({
([      "action" : "$N单掌一抖，运聚先天功功力，呼啸着向$n的$l处拍去",
        "dodge"  : -87,
        "force"  : 430,
        "attack" : 163,
        "parry"  : -81,
        "damage" : 83,
        "damage_type": "内伤"
]),
([      "action" : "$N右掌平伸，左掌运起先天功的劲力，猛地拍向$n的$l",
        "dodge"  : -85,
        "force"  : 440,
        "attack" : 147,
        "parry"  : -77,
        "damage" : 81,
        "damage_type": "内伤"
]),
([      "action" : "$N身形一展，右掌护住心脉，左掌中攻直进，贯向$n$l",
        "dodge"  : -75,
        "force"  : 450,
        "attack" : 182,
        "parry"  : -67,
        "damage" : 93,
        "damage_type": "内伤"
]),
([      "action" : "$N运转先天真气，双掌回圈，顿时一波澎湃的气劲直袭$n",
        "dodge"  : -87,
        "force"  : 480,
        "attack" : 183,
        "parry"  : -85,
        "damage" : 105,
        "damage_type": "内伤"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("xiantian-gong", 1);

        if (lvl >= 180)
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";

}

int valid_learn(object me)
{
        if( query("character", me) != "光明磊落"
            && query("character", me) != "国士无双" )
                return notify_fail("你只觉先天功正大恢弘，依自己的天性似乎难以领悟。\n");

        /*
        if( query("int", me)<28 )
                return notify_fail("你的先天悟性不足，难以领会高深的先天功。\n");
        */

        if( query("con", me)<32 )
                return notify_fail("你的先天根骨孱弱，无法修炼高深的先天功。\n");

        if( query("gender", me) == "无性" && query("xiantian-gong", me)>29 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的先天功。\n");

        if ((int)me->query_skill("taoism", 1) < 200)
                return notify_fail("你对道学心法的理解不够，难以领会先天功。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功火候不足，难以领会先天功。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳脚火候不足，难以领会先天功。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以领会先天功。\n");

        if (me->query_skill("taoism", 1) < 320
           && me->query_skill("taoism", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("你对道学心法的理解不够，难以锻炼更深厚的先天功。\n");

        if (me->query_skill("force", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("你的基本内功水平不够，难以锻炼更深厚的先天功。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("你的基本拳脚水平不够，难以锻炼更深厚的先天功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("xiantian-gong", 1);

        if (damage_bonus < 50
           || lvl < 180)
                return 0;

        if (damage_bonus > victim->query_con()/10)
        {
                addn("neili", -30, me);
                victim->receive_wound("qi", damage_bonus / 2, me);
                return HIR"随着""$N""的攻击,一股先天纯阳真力瞬间爆发了出来，$n"  //return HIW "$N" HIW "先天功的潜力发挥了出来，突然间$n"
                       HIR "只感五内俱焚，喉咙沙哑无比，不禁咳一口鲜血！\n" NOR;// HIW "只感喉咙一甜，喷出一口鲜血！\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("先天功只能用学(learn)来增加熟练度。\n");
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
//        if ((int)this_player()->query("int") < 28)
//                return "你的先天悟性不够，无法知晓如何运用先天功绝招。\n";

        return __DIR__"xiantian-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"xiantian-gong/exert/" + action;
}

/*
void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("xiantian-gong", 1);

        if (lvl > 220
         && query("can_exert/xiantian-gong/shentong", me) <= 60 )
        {
                if( me->add("can_exert/xiantian-gong/shentong",random(i))<60 )
                {
                        tell_object(me, HIC "你对先天功「" HIW "纯阳神通功"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了先天功「" HIW "纯阳神通功"
                                        HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }
}
*/

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        int ap, dp, cost;
        mapping result;

        if (me->query_skill("xiantian-gong", 1) < 200 ||
            me->query_skill_mapped("force") != "xiantian-gong" ||
            query("neili", me)<1000 ||
            ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap=ob->query_skill("force")*12+query("max_neili", ob)+ob->query_skill("count",1);
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "只见$n" HIR "先天护体神功自然而"
                                            "然发动，将$N" HIR "的力道尽数反震回"
                                            "去。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "只见$n" HIR "先天护体神功自然而"
                                            "然发动，将$N" HIR "的攻击化为无形。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "只见$n" HIR "先天护体神功自然而"
                                            "然发动，抵抗$N" HIR "的攻击。\n" NOR]);
                        break;
                }
                return result;
        }
}
