// This program is a part of NITAN MudLIB
// liuhe-dao.c 丐帮六合刀法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action":"$N大喝一声，手中$w大开大阖，连连挥刀使出「呵壁问天」，斩向$n的$l",
        "attack": 55,
        "dodge" : 56,
        "parry" : 54,
        "damage": 120,
        "lvl" : 0,
        "skill_name" : "呵壁问天",
        "damage_type":  "割伤"
]),
([      "action":"$N运刀如风，一招「气盖河山」，刀势霸道之极，向着$n周身各处猛砍猛劈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 65,
        "damage": 130,
        "lvl" : 10,
        "skill_name" : "气盖河山",
        "damage_type":  "割伤"
]),
([      "action":"$N一着「天地乍合」，突然抢进$n近侧，迅猛地驱刀连斩，攻式顿然合成一个圆圈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 55,
        "damage": 140,
        "lvl" : 25,
        "skill_name" : "天地乍合",
        "damage_type":  "割伤"
]),
([      "action":"$N仰天悲笑，随即挥刀斩出一式「离合无常」，$w化为一丝丝寒意，裹向$n$l",
        "attack": 70,
        "dodge" : 65,
        "parry" : 70,
        "damage": 140,
        "lvl" : 35,
        "skill_name" : "离合无常",
        "damage_type":  "割伤"
]),
([      "action":"$N施展「和合六出」绕着$n飞旋，$w带着狂野刀风，凌历无比地劈出六刀",
        "attack": 63,
        "dodge" : 60,
        "parry" : 70,
        "damage": 145,
        "lvl" : 45,
        "skill_name" : "和合六出",
        "damage_type":  "割伤"
]),
([      "action":"$N脸色庄重，挥刀使出「阴阳隔阂」，$w由上而下向$n连劈，犹似一个个焦雷轰顶",
        "attack": 70,
        "dodge" : 70,
        "parry" : 75,
        "damage": 145,
        "lvl" : 60,
        "skill_name" : "阴阳隔阂",
        "damage_type":  "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("你的混天气功火候太浅。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 5;
        int p_e2 = -15;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 50;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("liuhe-dao", 1);
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
                "damage_type" : "割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练六合刀法。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练六合刀法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuhe-dao/" + action;
}

int learn_bonus() { return 20; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n六合刀法："NOR"\n");
        write(@HELP

    四象六合刀为丐帮的刀法。

        学习要求：
                混天气功30级
                内力50
HELP
        );
        return 1;
}