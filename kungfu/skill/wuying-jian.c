//wuying-jian 少林无影剑
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N握紧手中$w一招「来去自如」点向$n的$l",
        "force" : 50,
        "dodge" : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "来去自如", 
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「日月无光」，无数$w上下刺出，直向$n逼去",
        "force" : 70,
        "dodge" : 10,
        "damage" : 30,
        "lvl"    : 20,
        "skill_name" : "日月无光",
        "damage_type" : "刺伤"
]),
([      "action" : "$N向前跨上一步，手中$w使出「剑气封喉」直刺$n的喉部",
        "force" : 90,
        "dodge" : 80,
        "damage" : 50,
        "lvl"    : 40,
        "skill_name" : "剑气封喉",
        "damage_type" : "刺伤"
]),
([      "action" : "$N虚恍一步，使出「心境如水」手中$w直刺$n的要害",
        "force" : 90,
        "dodge" : 60,
        "damage" : 80,
        "lvl"    : 60,
        "skill_name" : "心境如水",
        "damage_type" : "刺伤"
]),
([      "action" : "只见$N抡起手中的$w，使出「佛光普照」万点金光直射$n",
        "force" : 90,
        "dodge" : 70,
        "damage" : 110,
        "lvl"    : 80,
        "skill_name" : "佛光普照",
        "damage_type" : "刺伤"
]),
([      "action" : "$N抡起手中的$w，使出「风行叶落」无数剑光直射$n",
        "force" : 120,
        "dodge" : 60,
        "damage" : 120,
        "lvl"    : 100,
        "skill_name" : "风行叶落", 
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出「声东击西」，手中$w如刮起狂风一般闪烁不定，刺向$n",
        "force" : 200,
        "dodge" : 80,
        "damage" : 140,
        "lvl"    : 120,
        "skill_name" : "声东击西",
        "damage_type" : "刺伤"
]),
([      "action" : "$N随手使出剑法之奥义「无影无踪」，手中$w如鬼魅一般铺天盖地的刺向$n",
        "force" : 300,
        "dodge" : 90,
        "damage" : 250,
        "lvl"    : 150,
        "skill_name" : "「无影无踪」",
        "damage_type" : "刺伤"
]),
([      "action" : HIY"$N使出无影剑法之最终绝技[1;36m「蛟龙出水」[0m,[1;33m手中$w犹如蛟龙一般刺向$n[0m"NOR,
        "force" : 400,
        "dodge" : 100,
        "damage" : 800,
        "lvl"    : 220,
        "skill_name" : "HIY「剑气合一」"NOR,
        "damage_type" : "刺伤"
]),



});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("你的「混元一气」火候不够，无法学「无影剑法」。\n");
        if( query("max_neili", me)<300 )
                return notify_fail("你的内力太弱，无法练「无影剑法」。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("wuying-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/4)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的体力不够练「无影剑法」。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的内力不够练「无影剑法」。\n");
        me->receive_damage("qi", 40);
        addn("neili", -15, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuying-jian/" + action;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2) > victim->query_str() ) {
//                victim->add("qi", 1 - damage_bonus - 100 * 3 );
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                return HIR "你听到「哧」一声轻响一道霸气扑天而来，忽然间$n血冒三丈，被$N剑气所伤！\n";
        }
}


*/