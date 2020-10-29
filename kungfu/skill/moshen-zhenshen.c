// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以修习这等神功。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力还不足以修习这等神功。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("moshen-zhenshen", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的魔神真身。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("moshen-zhenshen", 1) < 100 ||
            query("family/family_name", ob) == "少林派" || 
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1) * 12;
        ap=ob->query_skill("force")*12+query("max_neili", ob)+mp;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);
 
                result += (["msg" : HIY "$n" HIY "内力一阵鼓荡，形成一个无影的墙壁，挡开了$N"
                                    HIY "的攻击。\n" NOR]);
 
                return result;
        }
        else if (mp >= 100)
        {
                result = HIY "$n身前仿佛有一道无形气墙，但$N早已看破$n破绽，直攻向$n要害。\n";

                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("moshen-zhenshen", 1);
        if (lvl < 100) return 0;
        if (lvl < 150) return 50;
        if (lvl < 200) return 60;
        if (lvl < 250) return 70;
        if (lvl < 300) return 80;
        if (lvl < 350) return 90;
        if (lvl < 400) return 100;
        return 120;
}

int practice_skill(object me)
{
        return notify_fail("魔神真身只能用学习或研究来提高。\n"); 
        if (me->query_skill("moshen-zhenshen", 1) < 100)
                return notify_fail("你对魔神真身的了解甚浅，还不足以自行锻炼。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够练护体神功。\n");

        me->receive_damage("qi", 50);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-zhenshen/" + action;
}