//lingshe_zhangfa.c 灵蛇杖法

#include "ansi.h"
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使出一招"HIB"「灵蛇出洞」"NOR"，手中$w大开大阖扫向$n的$l",
        "lvl"    : 0,
        "skill_name" : "灵蛇出洞"
]),
([        "action" : "$N手中$w阵阵风响，一招"BLU"「摇头摆尾」"NOR"向$n的$l攻去",
        "lvl"    : 20,
        "skill_name" : "摇头摆尾"
]),
([        "action" : "$N举起$w，居高临下使一招"MAG"「灵蛇下涧」"NOR"砸向$n的$l",
        "lvl"    : 30,
        "skill_name" : "灵蛇下涧"
]),
([        "action" : "$N一招"HIM"「灵蛇挺身」"NOR"，手中$w猛烈扫向$n的$l",
        "lvl"    : 40,
        "skill_name" : "灵蛇挺身"
]),
([        "action" : "$N使出一招"YEL"「蛇游蟒走」"NOR"，$w左右迂回向$n的$l扫去",
        "lvl"    : 50,
        "skill_name" : "蛇游蟒走"
]),
([        "action" : "$N手中$w一挥，使出一招"MAG"「蛇缠左右」"NOR"，忽左忽右扫向$n的$l",
        "lvl"    : 60,
        "skill_name" : "蛇缠左右"
]),
([        "action" : "$N使出一招"RED"「巨蟒下山」"NOR"，高举手中$w，劈头砸向$n的$l",
        "lvl"    : 80,
        "skill_name" : "巨蟒下山"
]),
([        "action" : "$N使出一招"HIR"「灵蛇出洞」"NOR"，手中$w猛一探，直扫$n的$l",
        "lvl"    : 100,
        "skill_name" : "灵蛇出洞"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法还不到家，不能学习灵蛇杖法。\n");

        if ((int)me->query_skill("staff", 1) < me->query_skil("linshe-zhangfa", 1))
                return notify_fail("你的基本杖法水平不够，无法领会更高深的灵蛇杖法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练灵蛇杖法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练灵蛇杖法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl,flvl;
        lvl = me->query_skill("lingshe-zhangfa",1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;
        if (!query_temp("weapon", me) || !query("snake_type", (query_temp("weapon", me))))
                       return;

       if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
              victim->affect_by("snake_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
       {
                return HIR "只听$n痛呼了一声，却是被蛇杖顶端的小蛇咬了个正着！\n" NOR;
       }
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 5;
        int p_e2 = 40;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 210;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("lingshe-zhangfa", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫伤",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"lingshe-zhangfa/" + action;
}
int help(object me)
{
        write(HIC"\n灵蛇杖法："NOR"\n");
        write(@HELP

    灵蛇杖法是西毒欧阳锋的歹毒武功。杖法凶狠，兼且杖头毒蛇
乘隙伤人，甚是阴毒。

        学习要求：
                蛤蟆功20级
                内力修为70
HELP
        );
        return 1;
}
