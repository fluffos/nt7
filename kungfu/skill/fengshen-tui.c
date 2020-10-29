#include <ansi.h>
inherit SKILL;
//By dream 简单版，待修改

string *dodge_msg = ({
    "只见$n一招[1;32m「捕风捉影」[2;37;0m，身化无影，快若流星地躲过了$N这一招。\n",
    "$n急用一招[1;36m「风中劲草」[2;37;0m，向后纵出数丈之远，避开了$N的凌厉攻势。\n",
    "$n使出[1;34m「暴雨狂风」[2;37;0m，猛烈的气势压的$N全部攻击不自觉地落了空。\n"
    "但是$n身影快如闪电，一招[1;31m「雷厉风行」[2;37;0m，轻松躲过了$N的攻击。\n",
    "$n身随意转，一招[1;35m「风卷楼残」[2;37;0m避过了$N这一招。\n",
    "$n使用一招[1;37m「神风怒嚎」[2;37;0m，顿时$N连$n的身影都看不见了。\n"
});

int valid_enable(string usage) 
{ 
        return usage == "dodge"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你基本轻功修为有限，难以修炼风神腿。\n");

        if ((int)me->query_skill("bingxin-jue", 1) < 80)
                return notify_fail("你冰心决修为不够，难以修炼风神腿。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你内力修为太浅，难以修炼风神腿。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

int practice_skill(object me)
{
        if( query("qi", me)<200 )
                return notify_fail("你的体力太差了，不能练风神腿。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力太差了，不能练习风神腿。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
string perform_action_file(string action)
{
      return __DIR__"fengshen-tui/" + action;
}
