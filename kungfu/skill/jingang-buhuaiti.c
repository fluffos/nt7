// jingang-buhuaiti.c

#include <ansi.h>

inherit SHAOLIN_SKILL;

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以修习这等神功。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力还不足以修习这等神功。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("jingang-buhuaiti", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的金刚不坏体神功。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("jingang-buhuaiti", 1) < 200 ||
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1) * 12;
        ap=ob->query_skill("force")*12+query("max_neili", ob)+mp;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(5))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "身前仿佛有一道无形气墙，让$N"
                                            HIY "再难前进一步。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "只见$N" HIY "这一招打了个正中！然而$n"
                                            HIY "毫不在意，并没有放在心上。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIY "$N" HIY "一招正好打在$n" HIY "身上，可"
                                            "力量犹如石沉大海，丝毫不起作用。\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIY "$N" HIY "一招击在$n" HIY "身上，可听$n"
                                            HIY "一声大喝，$N" HIY "反被护体罡气震退了"
                                            "数步。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "浑若无事的接下了$N"
                                            HIY "这一招，却没有受到半点伤害。\n" NOR]);
                        break;
                }
                return result;
        }
        else if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$n身前仿佛有一道无形气墙，但$N早已看破$n的诡计，直攻其要害。\n";
                        break;
                case 1:
                        result = HIY "$n浑若无事的接下了这一招，却意外地受到了伤害。\n";
                        break;
                case 2:
                        result = HIY "可是$N看出了$n的金刚不坏的气门所在，招式变幻莫测，双手遥指$n气门,$n心里一慌，真气流畅不顺，露出了破绽。\n";
                        break;
                default:
                        result = HIY "只见$N这一招打了个正中！大喝一声“破！”，结果正中$n要害。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jingang-buhuaiti", 1);
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
        if (me->query_skill("jingang-buhuaiti", 1) < 100)
                return notify_fail("你对这门护体神功的了解甚浅，还不足以自行锻炼。\n");

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
        return __DIR__"jingang-buhuaiti/" + action;
}
