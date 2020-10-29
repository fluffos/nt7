// xuantian-zhi.c 玄天无情指
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int is_pbsk() { return 1; }

mapping *action = ({
([        "action" : "$N左指挥出，一式"BLU"「黯然消魂」"NOR"，削向$n的掌缘",
        "lvl" : 0,
        "skill_name" : "黯然消魂"
]),
([        "action" : "$N全身之力聚于一指，一式"HIC"「天似无情」"NOR"，指向$n的胸前",
        "lvl" : 15,
        "skill_name" : "天似无情"
]),
([        "action" : "$N左掌贴于神道穴，右手一式"MAG"「情根深种」"NOR"，向$n的$l划过",
        "lvl" : 25,
        "skill_name" : "情根深种"
]),
([        "action" : "$N双目怒视，一式"CYN"「情在天涯」"NOR"，双指拂向$n的额、颈、肩、臂、胸
、背",
        "lvl" : 45,
        "skill_name" : "情在天涯"
]),
([        "action" : "$N一式"HIR"「独饮情伤」"NOR"，左掌掌心向外，右指蓄势点向$n的$l",
        "lvl" : 60,
        "skill_name" : "独饮情伤"
]),
([        "action" : "$N右手伸出，十指叉开，一式"HIW"「无诉别情」"NOR"，小指拂向$n的太渊穴",
        "lvl" : 70,
        "skill_name" : "无诉别情"
]),
([        "action" : "$N双迸出无数道劲气，一式"HIG"「情意绵绵」"NOR"射向$n的全身",
        "lvl" : 80,
        "skill_name" : "情意绵绵"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练玄天指必须空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法学玄天指。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力太弱，无法练玄天指。\n");

        if ((int)me->query_skill("finger", 1) < 80)
                return notify_fail("你的基本指法火候不够，无法练玄天指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("xuantian-zhi", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的玄天指。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("jing", me)<40 )
                return notify_fail("你的精太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够练玄天无情指。\n");
        me->receive_damage("jing", 35);
        addn("neili", -15, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("xuantian-zhi", 1);
        flvl=query("jiali", me);
        if (lvl < 100 || flvl < 20 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xuantian_zhi",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return HIW "$n" HIW "只感觉阴寒之气攻心，全身瘫软，嘴皮乌紫，面庞竟笼罩了一层寒霜。\n" NOR;
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 240;
        int f_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xuantian-zhi", 1);
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
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"xuantian-zhi/" + action;
}

int help(object me)
{
        write(HIC"\n玄天无情指："NOR"\n");
        write(@HELP

    日月神教黑木崖武功。梅庄二庄主黑白子的凌厉指法，招数中
带有阴寒内劲，可伤人于无形之中。

        学习要求：
                葵花心法80级
                内力150
HELP
        );
        return 1;
}

