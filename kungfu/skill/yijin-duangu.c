#include <ansi.h>
inherit FORCE;

int is_pbsk() { return 1; }

int valid_enable(string usage)
{
        // return usage == "force" || usage == "parry";
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yijin-duangu", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([      "action":"$N默自运功，依照易筋锻骨的口诀将内息在周身经脉中游走了一遍"
]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}


int valid_learn(object me)
{
        if( query("gender", me) == "无性" && me->query_skill("yijin-duangu",1)>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的易筋锻骨内功。\n");

        if( query("character", me) == "狡黠多变" && query("yijin-duangu", me)>17000 )
                return notify_fail("这九阴真经中所记载的易筋锻骨正大恢弘，气度俨然，依照"
                                   "你狡黠多变的天性似乎只能学到这种程度。\n");

        if( query("character", me) == "心狠手辣" && query("yijin-duangu", me)>16000 )
                return notify_fail("这九阴真经中所记载的易筋锻骨正大恢弘，气度俨然，依照"
                                   "你心狠手辣的天性似乎只能学到这种程度。\n");

        if( query("character", me) == "阴险狡诈" && query("yijin-duangu", me)>15000 )
                return notify_fail("这九阴真经中所记载的易筋锻骨正大恢弘，气度俨然，依照"
                                   "你阴险狡诈的天性似乎只能学到这种程度。\n");
          if( query("con", me)<30 )
                  return notify_fail("你觉得自己先天根骨不足，一时难以修炼。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候还不够，还不能学习易筋锻骨内功。\n");

        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("yijin-duangu", 1))
                return notify_fail("你觉得自己的武学修养有限，难以领会更高深的易筋锻骨。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("易筋锻骨内功只能用学(learn)的来增加熟练度。\n");
        if( query("qi", me)<150 )
                return notify_fail("你的体力太差了，不能练习易筋锻骨。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力太差了，不能练习易筋锻骨。\n");

        me->receive_damage("qi", 100);
        addn("neili", -150, me);
        return 1;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("yijin-duangu", 1) < 100 ||
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("parry", 1);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIM"$n单手接下了$N这一招，却发出「锵」一声，"
                                            HIM"仿佛$n这只手是铁铸般。\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM"$N一招平实得打在$n身上，然而$N感觉像打到"
                                            HIM"棉花上一样，说不出的怪异。\n"NOR]);
                        break;
                default:
                        result += (["msg" : HIM"眼看$N这招逼得$n无路可逃，却见$n没了骨头"
                                            HIM"似的直摊了下去，使$N这招无功而返。\n"NOR]);
                        break;
                }
                return result;
        }
}
*/

string exert_function_file(string func)
{
        return __DIR__"yijin-duangu/" + func;
}
