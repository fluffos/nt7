// tianshan-zhang.c 天山杖法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$N使出一招"HIW"「冰河开冻」"NOR"，手中$w大开大阖扫向$n的$l",
        "lvl" : 1,
        "skill_name" : "冰河开冻"
]),
([        "action": "$N手中$w阵阵风响，一招"HIC"「山风凛冽」"NOR"向$n的$l攻去",
        "lvl" : 13,
        "skill_name" :"山风凛冽"
]),
([        "action": "$N举起$w，居高临下使一招"HIW"「天山雪崩」"NOR"砸向$n的$l",
        "lvl" : 30,
        "skill_name" : "天山雪崩"
]),
([        "action": "$N一招"HIR"「残阳照雪」"NOR"，纵身飘开数尺，手中$w砸向$n的$l",
        "lvl" : 45,
        "skill_name" : "残阳照雪"
]),
([        "action": "$N使一招"HIB"「回光幻电」"NOR"，手中$w幻一条疾光点向$n的$l",
        "lvl" : 60,
        "skill_name" : "回光幻电"
]),
([        "action": "$N使出的"HIC"「风霜碎影」"NOR"，$w连挥杖影霍霍劈向$n的$l",
        "lvl" : 75,
        "skill_name" : "风霜碎影"
]),
([        "action": "$N的$w凭空一指，一招"BLU"「断石狼烟」"NOR"点向$n的$l",
        "lvl" : 90,
        "skill_name" : "断石狼烟"
]),
([        "action": "$N纵身一跃，手中$w一招"MAG"「长空雷隐」"NOR"对准$n的$l扫去",
        "lvl" : 105,
        "skill_name" : "长空雷隐"
]),
([        "action": "$N手中$w中宫直进，一式"CYN"「冰谷初虹」"NOR"对准$n的$l点去",
        "lvl" : 120,
        "skill_name" : "冰谷初虹"
]),
([        "action": "$N一招"GRN"「峰回路转」"NOR"，$w左右迂回向$n的$l点去",
        "lvl" : 145,
        "skill_name" : "峰回路转"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if (me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，不能学习天山杖法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够，不能学习天山杖法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("tianshan-zhang", 1))
                return notify_fail("你的基本杖法水平有限，无法领会更高深的天山杖法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<50 || query("neili", me)<30 )
                return notify_fail("你的内力或气不够练天山杖法。\n");
        me->receive_damage("qi", 40);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
string perform_action_file(string action)
{
        return __DIR__"tianshan-zhang/" + action;
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -40;
        int d_e2 = -10;
        int p_e1 = 15;
        int p_e2 = 50;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 180;
        int m_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tianshan-zhang", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }
mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        object weapon;
        string msg;
        int ap, dp;

        if( !objectp(weapon=query_temp("weapon", me) )
        ||  damage < 50)
                return 0;

        ap=query("level", me);
        ap += me->query_skill("staff");
        dp=query("level", me);
        dp += victim->query_skill("parry");

        ap = (ap + random(ap * 2)) / 2;

        if( query_temp("pifeng", me) )
        {
                if (random(ap + dp) > ap)
                {
                        msg=HIW"\n$N一声怒喝，手中"+query("name", weapon)+HIW"舞地风声大作，本以复杂的招数更是难辨。\n"NOR;
                        if (! victim->is_busy())
                                victim->start_busy(1);

                        result = ([ "msg" : msg, "damage" : damage / 2 ]);
                }
                else if (random(ap + 2 * dp) > ap)
                {
                        msg=YEL"\n$N将手中"+query("name", weapon)+YEL"向$n脚下扫去，趁$n躲闪之际，猛地发出一击！\n"NOR;
                        if (! victim->is_busy())
                        victim->start_busy(1+random(3));

                        result = ([ "msg" : msg, "damage" : damage ]);
                }
                else
                {
                        msg = HIR "\n$N陡然杖法一变，风声渐轻，而招数变得诡异莫测，吞吐不定。\n" NOR;
                        if (! victim->is_busy())
                        victim->start_busy(random(2));

                        result = ([ "msg" : msg, "damage" : damage / 3]);
                }

                return result;
        }
}

int help(object me)
{
        write(HIC"\n天山杖法\n");
        write(@HELP

    天山杖法是星宿派器械功夫。

        学习要求：
                化功大法20级
                内力80
HELP
        );
        return 1;
}
